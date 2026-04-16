#pragma once
#include "../../Uefi.h"
#include "../../Nca/Nca.h"

extern
UINT64
AsmInterlockedLoad(
	UINT64* _In_ Alias
);

extern
VOID
AsmInterlockedStore(
	UINT64* _In_ Alias,
	UINT64 Value
);

extern
UINT64
AsmInterlockedCompareExchange(
	UINT64* _In_ Alias,
	UINT64 Value,
	UINT64 Comparison
);

extern
UINT64
AsmInterlockedExchange(
	UINT64* _In_ Alias,
	UINT64 Value
);

extern
UINT64
AsmInterlockedAdd(
	UINT64* _In_ Alias,
	UINT64 ValueToAdd
);
