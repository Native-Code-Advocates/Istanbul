#include "Mem.h"
#include "../Arch/x86/Interlocked.h"
#include "../Arch/x86/Cpu.h"
#include "Utils.h"
#include "../Istanbul.h"

// yes im not merging free blocks
// im well aware of that.

VOID* gIbScratchHeap;
INT8* gIbScratchCursor;
UINT64 gIbScratchHeapLimit;

SPIN_LOCK gLinearMapLock = 0;
SPIN_LOCK gMemoryMapLock = 0;

LIST_ENTRY gMemoryMap _Guarded_by_(gMemoryMapLock);

VOID* PoolScratch;
UINT64 PoolScratchCursor;

VOID* _Out_
IbpAllocateScratch(
	UINTN Size
) {
	// allocate on 64-bit aligned sizes. last thing we need is an unaligned allocation
	ASSERT((Size & 0b111) != 0);
	ASSERT((UINT64)gIbScratchCursor + Size < gIbScratchHeapLimit);	
	
	return (VOID*)AsmInterlockedAdd((UINT64*)&gIbScratchCursor, Size);
}

VOID
IbpMemInitialize(
	ISTANBUL_BOOT_DATA* _In_ BootData
) {
	gIbScratchHeap = (VOID*)ISTANBUL_SCRATCH_BEGIN;
	gIbScratchCursor = (INT8*)0;
	gIbScratchHeapLimit = ISTANBUL_SCRATCH_END;

	// CONTRACT:
	// hypervisor guarantees a contigious address space from ISTANBUL_HEAP_MAX to BootData->MemorySize that is available to use.
	// hardware data like ACPI tables, PCIe templates are stored between 0x0-ISTANBUL_HEAP_MAX.
	ISTANBUL_MEMORY_MAP* InitialFree = (ISTANBUL_MEMORY_MAP*)IbpAllocateScratch(sizeof(ISTANBUL_MEMORY_MAP));
	InitialFree->Start = ISTANBUL_HEAP_MAX;
	InitialFree->End = BootData->MemorySize;
	InitialFree->Type = EfiConventionalMemory;
	InitialFree->VirtualStart = 0;

	InsertHeadList(&gMemoryMap,&InitialFree->Link);
}

static
ISTANBUL_MEMORY_MAP* _Out_opt_
IbpMemAllocateHole(
	ISTANBUL_MEMORY_MAP* _In_ FreeEntry,
	EFI_PHYSICAL_ADDRESS Start,
	EFI_PHYSICAL_ADDRESS NumberOfBytes,
	EFI_MEMORY_TYPE Type
) {
	ASSERT(FreeEntry->Type == EfiConventionalMemory);

	if (!(Start >= FreeEntry->Start && Start + NumberOfBytes <= FreeEntry->End)) {
		return NULL;
	}
	ISTANBUL_MEMORY_MAP* Hole = (ISTANBUL_MEMORY_MAP*)IbpAllocateScratch(sizeof(ISTANBUL_MEMORY_MAP));

	Hole->Start = Start;
	Hole->End = Start + NumberOfBytes;
	Hole->Type = Type;

	// we can actually use FreeEntry itself instead of making a new scratch allocation
	// but we wont

	if (Start != FreeEntry->Start) {
		ISTANBUL_MEMORY_MAP* Split = (ISTANBUL_MEMORY_MAP*)IbpAllocateScratch(sizeof(ISTANBUL_MEMORY_MAP));
		Split->Type = EfiConventionalMemory;
		Split->Start = FreeEntry->Start;
		Split->End = Start;
		InsertTailList(&gMemoryMap, &Split->Link);
	}

	if (Hole->End != FreeEntry->End) {
		ISTANBUL_MEMORY_MAP* Split = (ISTANBUL_MEMORY_MAP*)IbpAllocateScratch(sizeof(ISTANBUL_MEMORY_MAP));
		Split->Type = EfiConventionalMemory;
		Split->Start = Hole->End;
		Split->End = FreeEntry->End;
		InsertTailList(&gMemoryMap, &Split->Link);
	}

	RemoveEntryList(&FreeEntry->Link);
	InsertTailList(&gMemoryMap, &Hole->Link);

	return Hole;
}

static
ISTANBUL_MEMORY_MAP* _Out_opt_
IbpUefiReserveFreePages(
	UINT64 NumberOfPages,
	EFI_MEMORY_TYPE Type,
	EFI_PHYSICAL_ADDRESS* _Out_opt_ Address,
	EFI_PHYSICAL_ADDRESS* _In_opt_ MaximumAddress
) _Requires_lock_(gLinearMapLock) _Requires_lock_(gMemoryMapLock) {
	// both of them cannot be requested at the same time
	ASSERT(!(Address != NULL && MaximumAddress != NULL));
	ASSERT(NumberOfPages != 0);

	UINT64 Target = 0;
	if (Address != NULL)
		Target = *Address;

	UINT64 Maximum = -1ULL; // fuck cstdint
	if (MaximumAddress != NULL)
		Maximum = *MaximumAddress;

	UINT64 NumberOfBytes = NumberOfPages << 12;

	ISTANBUL_MEMORY_MAP* Hole = NULL;
	BOOLEAN Found = FALSE;

	for (LIST_ENTRY* Link = gMemoryMap.ForwardLink;
			Link != &gMemoryMap;
			Link = Link->ForwardLink) {
		Hole = (ISTANBUL_MEMORY_MAP*)Link;

		if (Hole->Type != EfiConventionalMemory) continue;

		// its AllocateAddress, we ignore Maximum
		if (Target != 0) {
			if (Target >= Hole->Start && NumberOfBytes <= (Hole->End - Target)) {
            	Found = TRUE;
            	break;
        	}
		} else {
			// OVERFLOWS, ALL I SEE ARE OVERFLOWS. HELP ME. THIS IS NOT A JOKE
			UINT64 HoleSize = Hole->End - Hole->Start;
			if (NumberOfBytes > HoleSize) continue;

			UINT64 EffectiveEnd = (Hole->End < Maximum) ? Hole->End : Maximum;

			if (EffectiveEnd > Hole->Start && NumberOfBytes <= (EffectiveEnd - Hole->Start)) {
				Target = Hole->Start;
				Found = TRUE;
				break;
			}
		}
	}

	if (!Found) {
		return NULL;
	}

	return IbpMemAllocateHole(Hole, Target, NumberOfBytes, Type);
}

static
EFI_STATUS
IbpUefiFreeFoundPages(
	EFI_PHYSICAL_ADDRESS Start,
	UINTN NumberOfPages
) _Requires_lock_(gMemoryMapLock) {
	UINT64 NumberOfBytes = NumberOfPages << 12;

	for(LIST_ENTRY* Link = gMemoryMap.ForwardLink;
		Link != &gMemoryMap;
		Link = Link->ForwardLink) {
			ISTANBUL_MEMORY_MAP* Entry = (ISTANBUL_MEMORY_MAP*)Link;

			// we need to find original entry
			if (Entry->Start != Start) continue;

			// are we freeing more than what we have?
			ASSERT(Entry->End >= (Entry->Start + NumberOfBytes));

			UINT64 Delta = Entry->End - (Entry->Start + NumberOfBytes);

			// are we freeing the entire pages?
			if (Delta != 0) {
				ISTANBUL_MEMORY_MAP* Remaining = (ISTANBUL_MEMORY_MAP*)IbpAllocateScratch(sizeof(ISTANBUL_MEMORY_MAP));

				Remaining->FromPages = TRUE;
				Remaining->Start = Entry->Start + NumberOfBytes;
				Remaining->End = Entry->End;
				Remaining->Type = Entry->Type;
				InsertTailList(&gMemoryMap, &Remaining->Link);
			}

			Entry->End = Entry->Start + NumberOfBytes;
            Entry->Type = EfiConventionalMemory;
			return EFI_SUCCESS;
		}

	return EFI_NOT_FOUND;
}

EFI_STATUS
IbUefiAllocatePages(
	EFI_ALLOCATE_TYPE Type,
	EFI_MEMORY_TYPE MemoryType,
	UINTN Pages,
	EFI_PHYSICAL_ADDRESS* _Out_ Memory
) {
	ISTANBUL_MEMORY_MAP* _Nullable Map = NULL;

	IbUefiSpinLock(&gLinearMapLock);
	IbUefiSpinLock(&gMemoryMapLock);

	if (Type == AllocateAddress) {
		Map = IbpUefiReserveFreePages(Pages, MemoryType, Memory, NULL);
	} else if (Type == AllocateMaxAddress) {
		Map = IbpUefiReserveFreePages(Pages, MemoryType, NULL, Memory);
	} else {
		Map = IbpUefiReserveFreePages(Pages, MemoryType, NULL, NULL);
	}

	IbUefiSpinUnLock(&gLinearMapLock);
	IbUefiSpinUnLock(&gMemoryMapLock);

	if (Map == NULL) return EFI_NOT_FOUND;

	*Memory = Map->Start;
	return EFI_SUCCESS;
}

EFI_STATUS
IbUefiFreePages(
	EFI_PHYSICAL_ADDRESS Memory,
	UINTN Pages
) {
	IbUefiSpinLock(&gMemoryMapLock);

	EFI_STATUS Status = IbpUefiFreeFoundPages(Memory, Pages);

	IbUefiSpinUnLock(&gMemoryMapLock);

	return Status;
}

EFI_STATUS
IbUefiAllocatePool(
	EFI_MEMORY_TYPE Type,
	UINTN Size,
	VOID* _Out_ * _Out_ Buffer
) {
	return IbUefiAllocatePages(AllocateAnyPages,Type, Size / 4096, (EFI_PHYSICAL_ADDRESS*)Buffer);
}

EFI_STATUS
IbUefiFreePool(
	VOID* _In_ Buffer
) {
	for(LIST_ENTRY* Link = gMemoryMap.ForwardLink;
		Link != &gMemoryMap;
		Link = Link->ForwardLink) {
		ISTANBUL_MEMORY_MAP* Entry = (ISTANBUL_MEMORY_MAP*)Link;

		if (Entry->Start == (UINT64)Buffer) {
			return IbpUefiFreeFoundPages(Entry->Start, (Entry->End - Entry->Start) / 4096);
		}
	}

	return EFI_NOT_FOUND;
}