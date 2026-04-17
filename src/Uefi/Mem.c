#include "Mem.h"
#include "../Arch/x86/Cpu.h"
#include "../Istanbul.h"
#include "Utils.h"

ISTANBUL_PAGE_ALLOCATION* MemoryBitmap;
UINT64 MemorySize;
LIST_ENTRY PoolAllocations;

VOID
IbpMemInitialize(
	ISTANBUL_BOOT_DATA* _In_ BootData
) {
	MemoryBitmap = (ISTANBUL_PAGE_ALLOCATION*)BootData->MemoryBitmap;
	MemorySize = BootData->MemorySize;
}

static
VOID* _Out_opt_
IbAllocatePages(
	UINT64 MaximumAddress,
	UINT64 MinimumAddress,
	UINTN NumberOfPages,
	EFI_MEMORY_TYPE Type
) {
	if (MaximumAddress >= MemorySize) return NULL;

	MaximumAddress &= ~0xFFFULL;
	MaximumAddress = MaximumAddress >> 12;
	MinimumAddress &= ~0xFFFULL;
	MinimumAddress = MinimumAddress >> 12;

	ISTANBUL_PAGE_ALLOCATION* Allocation = NULL;
	UINTN ContinuousPages = 0, StartIndex = 0;
	for (UINTN i = MinimumAddress; i < MaximumAddress; i++) {
		if (MemoryBitmap[i].MemoryType == EfiConventionalMemory) {
			if (ContinuousPages == 0) StartIndex = i;
			ContinuousPages++;
			
			// make sure it satisfies us
			if (ContinuousPages == NumberOfPages) {
				Allocation = &MemoryBitmap[StartIndex];
				break; 
			}
		} else {
			// reset
			ContinuousPages = 0;
		}
	}

	if (Allocation == NULL) return NULL;

	// mark them used
	for (UINTN i = 0; i < NumberOfPages; i++) {
		Allocation[i].MemoryType = (UINT8)Type;
	}

	return Allocation;
}

static
VOID
IbFreePages(
	UINT64 StartAddress,
	UINTN NumberOfPages
) {
	ISTANBUL_PAGE_ALLOCATION* Allocation = &MemoryBitmap[StartAddress >> 12];
	for (UINTN i = 0; i < NumberOfPages; i++){
		Allocation[i].MemoryType = (UINT8)EfiConventionalMemory;
	}
}

EFI_STATUS
IbUefiAllocatePool(
	EFI_MEMORY_TYPE Type,
	UINTN Size,
	VOID* _Out_ * _Out_ Buffer
) {
	ISTANBUL_POOL_ALLOCATION* Allocation = (ISTANBUL_POOL_ALLOCATION*)IbAllocatePages(MAX_ADDR, MIN_ADDR, 1, Type);
	VOID* Block = IbAllocatePages(MAX_ADDR, MIN_ADDR, Size >> 12, Type);
	if (Allocation == NULL || Block == NULL) {
		if (Allocation != NULL) IbFreePages((UINT64)Allocation, 1);
		if (Block != NULL) IbFreePages((UINT64)Block, Size >> 12);
		return EFI_NOT_FOUND;
	}

	Allocation->Start = (EFI_PHYSICAL_ADDRESS)Block;
	Allocation->NumberOfBytes = Size;

	InsertTailList(&PoolAllocations, &Allocation->Link);

	*Buffer = Block;

	return EFI_SUCCESS;
}

EFI_STATUS
IbUefiFreePool(
	VOID* _In_ Buffer
) {
	for (LIST_ENTRY* Link = PoolAllocations.ForwardLink; Link != &PoolAllocations; Link = Link->ForwardLink) {
		ISTANBUL_POOL_ALLOCATION* Allocation = (ISTANBUL_POOL_ALLOCATION*)Link;

		if (Allocation->Start != (EFI_PHYSICAL_ADDRESS)Buffer) continue;

		IbFreePages((UINT64)Link, 1);
		IbFreePages((UINT64)Allocation->Start, Allocation->NumberOfBytes >> 12);
		return EFI_SUCCESS;
	}

	return EFI_NOT_FOUND;
}

EFI_STATUS
IbUefiFreePages(
	EFI_PHYSICAL_ADDRESS Memory,
	UINTN Pages
) {
	IbFreePages(Memory, Pages);
	return EFI_SUCCESS;
}

EFI_STATUS
IbUefiAllocatePages(
	EFI_ALLOCATE_TYPE Type,
	EFI_MEMORY_TYPE MemoryType,
	UINTN Pages,
	EFI_PHYSICAL_ADDRESS* _Out_ Memory
) {
	UINT64 MaximumAddress = MAX_ADDR, MinimumAddress = MIN_ADDR;
	switch (Type) {
		case AllocateAddress:
			MaximumAddress = ~0ULL;
			MinimumAddress = *Memory;
			break;
		case AllocateAnyPages:
			MaximumAddress = ~0ULL;
			break;
		case AllocateMaxAddress:
			MaximumAddress = *Memory;
			break;
		case MaxAllocateType:
			ASSERT(FALSE);
			break;
	}

	EFI_PHYSICAL_ADDRESS Allocation = (EFI_PHYSICAL_ADDRESS)IbAllocatePages(MaximumAddress, MinimumAddress, Pages,MemoryType);
	if (Allocation == NULL) {
		return EFI_NOT_FOUND;
	}

	*Memory = Allocation;
	return EFI_SUCCESS;
}