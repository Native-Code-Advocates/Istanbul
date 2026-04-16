#include "Utils.h"
#include "../Arch/x86/Interlocked.h"
#include "../Arch/x86/Cpu.h"

VOID
ASSERT(
	BOOLEAN Condition
) {
	if (!Condition) {
		AsmDebugBreakpoint();
	}
}

VOID
IbUefiMemSet(
	VOID* _Inout_ Memory,
	UINTN Length,
	INT8 Byte
) {
	INT8* Mem = (INT8*)Memory;
	for(UINTN Index = 0; Index < Length; Index++) {
		Mem[Index] = Byte;
	}
}

VOID
IbUefiSpinLock(
	SPIN_LOCK* _In_ SpinLock
) _Acquires_lock_(*SpinLock) {
	while (AsmInterlockedCompareExchange(SpinLock, 1, 0)) {
		// pause? not in my firmware
	}
}

VOID
IbUefiSpinUnLock(
	SPIN_LOCK* _In_ SpinLock
) _Releases_lock_(*SpinLock) {
	AsmInterlockedStore(SpinLock, 0);
}

VOID
InitializeListHead(
	LIST_ENTRY* _In_ ListHead
) {
	ListHead->ForwardLink = ListHead;
	ListHead->BackLink = ListHead;
}

VOID
InsertHeadList(
	LIST_ENTRY* _In_ ListHead,
	LIST_ENTRY* _In_ Entry
) {
	Entry->ForwardLink = ListHead->ForwardLink;
	Entry->BackLink = ListHead;
	Entry->ForwardLink->BackLink = Entry;
	ListHead->ForwardLink = Entry;
}

VOID
InsertTailList(
	LIST_ENTRY* _In_ ListHead,
	LIST_ENTRY* _In_ Entry
) {
	Entry->ForwardLink = ListHead;
	Entry->BackLink = ListHead->BackLink;

	Entry->BackLink->ForwardLink = Entry;
	ListHead->BackLink = Entry;
}

LIST_ENTRY* _Out_
RemoveEntryList(
	LIST_ENTRY* _In_ Entry
) {
	Entry->BackLink->ForwardLink = Entry->ForwardLink;
	Entry->ForwardLink->BackLink = Entry->BackLink;
	return Entry->ForwardLink;
}
