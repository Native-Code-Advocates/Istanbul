#pragma once
#include "../Uefi.h"
#include "Utils.h"
#include "../Istanbul.h"

#define ISTANBUL_HEAP_BEGIN 0x3000
#define ISTANBUL_HEAP_MAX 0x50000

#define ISTANBUL_SCRATCH_BEGIN 0x1000
#define ISTANBUL_SCRATCH_END 0x3000

#define MEMORY_INTERSECT(s1, e1, s2, e2) \
	((s1 <= e2) && (s2 <= e1))	

typedef struct {
	LIST_ENTRY Link;
	BOOLEAN FromPages;

	EFI_MEMORY_TYPE Type;
	UINT64 Start;
	UINT64 End;

	UINT64 VirtualStart;
	UINT64 Attribute;
} ISTANBUL_MEMORY_MAP; 

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