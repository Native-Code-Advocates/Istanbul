#pragma once
#include "Uefi.h"
#include "Arch/Acpi.h"

// Preferably mapped at 0x0
typedef struct {
	ACPI_RSDP Rsdp;
	VOID* PcieSpace;
	UINTN PcieSize;
	UINTN MemorySize;
	VOID* MemoryBitmap;
	UINTN LogicalProcessorCount;
} ISTANBUL_BOOT_DATA;

extern EFI_SYSTEM_TABLE gSystemTable;
extern EFI_BOOT_SERVICES gBootServices;
extern EFI_RUNTIME_SERVICES gRuntimeServices;
extern ISTANBUL_BOOT_DATA gBootData;