bits 64
global AsmDebugBreakpoint

section .text

; VOID AsmDebugBreakpoint(VOID)
; Triggers a debugger breakpoint.
AsmDebugBreakpoint:
	
	int 0x3
	ret
