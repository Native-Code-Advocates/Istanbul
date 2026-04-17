#include "Mem.h"
#include "../Arch/x86/Cpu.h"
#include "../Istanbul.h"

ISTANBUL_PAGE_ALLOCATION* MemoryBitmap;
UINT64 MemorySize;

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
		Allocation[i].MemoryType = Type;
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
		Allocation[i].MemoryType = EfiConventionalMemory;
	}
}

EFI_STATUS
IbUefiAllocatePages(
	EFI_ALLOCATE_TYPE Type,
	EFI_MEMORY_TYPE MemoryType,
	UINTN Pages,
	EFI_PHYSICAL_ADDRESS* _Out_ Memory
) {
	UINT64 MaximumAddress = 0, MinimumAddress = 0;
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