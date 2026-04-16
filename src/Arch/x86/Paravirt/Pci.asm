bits 64
extern IbpAsmVmcallStub

section .text

global IbpAsmSetPcieConfigSpace

; VOID IbpAsmSetPcieConfigSpace(VOID* Space);
; RCX = Pointer to buffer allocated
IbpAsmSetPcieConfigSpace:
    mov eax, 81
    jmp IbpAsmVmcallStub

; UINTN IbpAsmGetPcieConfigLength(VOID);
IbpAsmGetPcieConfigLength:
    mov eax, 65
    jmp IbpAsmVmcallStub