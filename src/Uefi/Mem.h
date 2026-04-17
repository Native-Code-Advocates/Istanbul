#pragma once
#include "../Uefi.h"
#include "Utils.h"
#include "../Istanbul.h"

#define MEMORY_INTERSECT(s1, e1, s2, e2) \
	((s1 <= e2) && (s2 <= e1))	

typedef struct {
	UINT8 MemoryType;
} _Packed_ ISTANBUL_PAGE_ALLOCATION;

VOID
IbpMemInitialize(
	ISTANBUL_BOOT_DATA* _In_ BootData
);

EFI_STATUS
IbUefiAllocatePages(
	EFI_ALLOCATE_TYPE Type,
	EFI_MEMORY_TYPE MemoryType,
	UINTN Pages,
	EFI_PHYSICAL_ADDRESS* _In_ Memory
);

EFI_STATUS
IbUefiFreePages(
	EFI_PHYSICAL_ADDRESS Memory,
	UINTN Pages
);

EFI_STATUS
IbUefiAllocatePool(
	EFI_MEMORY_TYPE Type,
	UINTN Size,
	VOID* _Out_ * _Out_ Buffer
);

EFI_STATUS
IbUefiFreePool(
	VOID* _In_ Buffer
);