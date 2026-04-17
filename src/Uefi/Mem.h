#pragma once
#include "../Uefi.h"
#include "Utils.h"
#include "../Istanbul.h"

#define MEMORY_INTERSECT(s1, e1, s2, e2) \
	((s1 <= e2) && (s2 <= e1))	

#define MAX_ADDR (~0ULL)
#define MIN_ADDR (0)

typedef struct {
	UINT8 MemoryType;
} _Packed_ ISTANBUL_PAGE_ALLOCATION;

typedef struct {
	LIST_ENTRY Link;
	EFI_PHYSICAL_ADDRESS Start;
	UINTN NumberOfBytes;
} ISTANBUL_POOL_ALLOCATION;

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

EFI_STATUS
IbUefiGetMemoryMap(
	UINTN* _Out_ MemoryMapSize,
	EFI_MEMORY_DESCRIPTOR* _Out_opt_ MemoryMap,
	UINTN* _Out_ MapKey,
	UINTN* _Out_ DescriptorSize,
	UINT32* _Out_ DescriptorVersion
);