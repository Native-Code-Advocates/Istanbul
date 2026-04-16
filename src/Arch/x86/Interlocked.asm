bits 64
global AsmInterlockedCompareExchange
global AsmInterlockedStore
global AsmInterlockedAdd

section .text

; UINT64 AsmInterlockedLoad(UINT64* Alias)
; RCX = Pointer to data to atomically acquire, must be 8 byte aligned
; Since aligned MOVs are atomic in x86...
AsmInterlockedLoad :

	mov rax, [rcx]
	; mfence
	ret
	
; VOID AsmInterlockedStore(UINT64* Alias, UINT64 Value)
; RCX = Pointer to data to atomically store, must be 8 byte aligned
; RDX = Value to put
; Since aligned MOVs are atomic in x86...
AsmInterlockedStore:

	mov [rcx], rdx
	; mfence
	ret
	
; UINT64 AsmInterlockedCompareExchange(UINT64* Alias, UINT64 Value, UINT64 Comparison)
; Checks if [Alias] is equal to Comparison, if so, replaces it with Value, atomically.
; RCX = Pointer to data to atomically store
; RDX = Value to put
; R8 = Comparison to make
AsmInterlockedCompareExchange:

	mov rax, r8

	lock cmpxchg [rcx], rdx

	ret

; UINT64 AsmInterlockedExchange(UINT64* Alias, UINT64 Value)
; Swaps the value of [Alias] with Value
; RCX = Pointer to data to atomically store
; RDX = Value to put
AsmInterlockedExchange:

	xchg [rcx], rdx
	mov rax, rdx
	ret


; UINT64 AsmInterlockedAdd(UINT64* Alias, UINT64 ValueToAdd)
; Increments [Alias] by ValueToAdd
; RCX = Pointer to data to atomically store
; RDX = Value to increment by
AsmInterlockedAdd:

	lock xadd [rcx], rdx
	ret
