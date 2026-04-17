#include "Nca/Nca.h"
#include "Uefi.h"
#include "Main.h"
#include "Istanbul.h"
#include "Uefi/Mem.h"
#include "Arch/x86/Paravirt/Variables.h"
#include "Arch/Pci.h"

EFI_SYSTEM_TABLE gSystemTable;
EFI_BOOT_SERVICES gBootServices;
EFI_RUNTIME_SERVICES gRuntimeServices;

static
EFI_STATUS
IbpUefiSetupBootServices(
	ISTANBUL_BOOT_DATA* _In_ BootData
) {

	IbpMemInitialize(BootData);

	gBootServices.AllocatePages = IbUefiAllocatePages;
	gBootServices.FreePages = IbUefiFreePages;
	gBootServices.AllocatePool = IbUefiAllocatePool;
	gBootServices.FreePool = IbUefiFreePool;
	gBootServices.GetMemoryMap = IbUefiGetMemoryMap;

	return EFI_SUCCESS;
}

static
EFI_STATUS
IbpUefiSetupRuntimeServices(
	ISTANBUL_BOOT_DATA* _In_ BootData
) {
	_Unused_var_(BootData);

	gRuntimeServices.SetVariable = IbpAsmSetVariable;
	gRuntimeServices.QueryVariableInfo = IbpAsmQueryVariableInfo;
	gRuntimeServices.GetVariable = IbpAsmGetVariable;
	gRuntimeServices.GetNextVariableName = IbpAsmGetNextVariableName;

	return EFI_SUCCESS;
}

EFI_STATUS
IbUefiMain(
	ISTANBUL_BOOT_DATA* _In_ BootData
) {
	// tables at the beginning are just reserved, first, we have to setup UEFI services

	gSystemTable.BootServices = &gBootServices;
	gSystemTable.RuntimeServices = &gRuntimeServices;

	IbpUefiSetupBootServices(BootData);
	IbpUefiSetupRuntimeServices(BootData);

	IbpPcieSetup(BootData);

	return EFI_SUCCESS;
}
