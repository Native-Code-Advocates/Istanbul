bits 64

section .text

global IbpAsmVmcallStub

IbpAsmVmcallStub:
    vmcall  ; where we were?
    ret