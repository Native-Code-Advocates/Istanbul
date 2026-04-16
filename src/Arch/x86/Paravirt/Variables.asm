bits 64
extern IbpAsmVmcallStub

section .text

global IbpAsmGetVariable
global IbpAsmSetVariable
global IbpAsmGetNextVariableName
global IbpAsmQueryVariableInfo

; Brief documentation of hypercall architecture
; Each hypercall is identified by RAX.
; RAX is divided into 2 fields. Last 4 bits are reserved to identify environment.
; UEFI (Boot services) =    0b0001
; SMM =                     0b0010
; Runtime (not UEFI) =      0b0100

; EFI_STATUS IbAsmGetVariable(CHAR16* VariableName, EFI_GUID* VendorGuid, UINT32* Attributes, UINTN* DataSize, VOID* Data)
; Reads a varible from host NVRAM store
; RCX = Pointer to variable's name. Unicode
; RDX = Pointer to EFI_GUID structure.
; R8 = Pointer to attributes returned. If null, ignored.
; R9 = Pointer to data size returned. If null, ignored.
; [RSP + 32] = Pointer to data that is returned
IbpAsmGetVariable:
    mov eax, 1
    jmp IbpAsmVmcallStub

; EFI_STATUS IbAsmSetVariable(CHAR16* VariableName, EFI_GUID* VendorGuid, UINT32 Attributes, UINTN DataSize, VOID* Data)
; Sets a variable at host NVRAM store
; RCX = Pointer to variable's name. Unicode
; RDX = Pointer to EFI_GUID structure.
; R8 = Attributes to set.
; R9 = DataSize to set.
; [RSP + 32] = Data to load.
IbpAsmSetVariable:
    mov eax, 17
    jmp IbpAsmVmcallStub

; EFI_STATUS IbAsmGetNextVariableName(UINTN* VariableNameSize, CHAR16* VariableName, EFI_GUID* VendorGuid)
; RCX = Pointer to size of variable name, in counts(?)
; RDX = Pointer to buffer to fill. If null, ignored.
; R8 = Pointer tto vendor guid
IbpAsmGetNextVariableName:
    mov eax, 33
    jmp IbpAsmVmcallStub

; EFI_STATUS IbAsmQueryVariableInfo(UINT32 Attributes, UINT64* MaximumVariableStorageSize, UINT64* RemainingVariableStorageSize, UINT64* MaximumVariableSize)
; RCX = Attribute bitmask to look for
; Read the spec dude I'm sick of writing more
IbpAsmQueryVariableInfo:
    mov eax, 49
    jmp IbpAsmVmcallStub