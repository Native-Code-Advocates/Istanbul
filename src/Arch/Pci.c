#include "../Istanbul.h"
#include "x86/Paravirt/Pci.h"

EFI_STATUS
IbpPcieSetup(
    ISTANBUL_BOOT_DATA* _In_ BootData
) {
    EFI_PHYSICAL_ADDRESS PcieSpace = 0;

    EFI_STATUS Status = gBootServices.AllocatePages(AllocateAnyPages, EfiACPIMemoryNVS, BootData->PcieSize / 4096, &PcieSpace);
    if(Status != EFI_SUCCESS) {
        return Status; 
    }

    BootData->PcieSpace = (VOID*)PcieSpace;

    IbpAsmSetPcieConfigSpace(BootData->PcieSpace);

    return EFI_SUCCESS;
}