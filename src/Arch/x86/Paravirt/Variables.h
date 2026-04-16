#include "../../../Uefi.h"
#include "../../../Nca/Nca.h"

extern
EFI_STATUS
IbpAsmGetVariable(
    CHAR16* _In_ VariableName,
    EFI_GUID* _In_ VendorGuid,
    UINT32* _Out_ Attributes,
    UINTN* _Out_opt_ DataSize,
    VOID* _Out_opt_ Data
);

extern
EFI_STATUS
IbpAsmSetVariable(
    CHAR16* _In_ VariableName,
    EFI_GUID* _In_ VendorGuid,
    UINT32 Attributes,
    UINTN DataSize,
    VOID* _In_ Data);

extern
EFI_STATUS 
IbpAsmGetNextVariableName(
    UINTN* _Out_ VariableNameSize,
    CHAR16* _Out_ VariableName,
    EFI_GUID* _Out_ VendorGuid
);

extern
EFI_STATUS
IbpAsmQueryVariableInfo(
    UINT32 Attributes,
    UINT64* _Out_ MaximumVariableStorageSize,
    UINT64* _Out_ RemainingVariableStorageSize,
    UINT64* _Out_ MaximumVariableSize
);