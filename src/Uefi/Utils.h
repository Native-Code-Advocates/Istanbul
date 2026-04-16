#pragma once
#include "../Uefi.h"
#include "../Nca/Nca.h"

typedef UINT64 SPIN_LOCK _Lockable_;

VOID
ASSERT(
	BOOLEAN Condition
);

VOID
IbUefiMemSet(
	VOID* _In_ Memory,
	UINTN Length,
	INT8 Byte
);

VOID
IbUefiSpinLock(
	SPIN_LOCK* _In_ SpinLock
) _Acquires_lock_(*SpinLock);

VOID
IbUefiSpinUnLock(
	SPIN_LOCK* _In_ SpinLock
) _Releases_lock_(*SpinLock);

VOID
InitializeListHead(
	LIST_ENTRY* _In_ ListHead
);

VOID
InsertHeadList(
	LIST_ENTRY* _In_ ListHead,
	LIST_ENTRY* _In_ Entry
);

VOID
InsertTailList(
	LIST_ENTRY* _In_ ListHead,
	LIST_ENTRY* _In_ Entry
);

LIST_ENTRY* _Out_
RemoveEntryList(
	LIST_ENTRY* _In_ ListEntry
);
