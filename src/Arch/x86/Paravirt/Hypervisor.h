#include "../../../Uefi.h"

typedef enum {
    HypercallUefiSetVariable = 0,           // 1
    HypercallUefiGetVariable = 1,           // 17
    HypercalluefiGetNextVariableName = 2,   // 33
    HypercallUefiQueryVariableInfo = 3,     // 49
    HypercallUefiGetPcieConfigSize = 4,     // 65
    HypercallUefiSetPcieConfigSpace = 5     // 81
} ISTANBUL_HYPERCALL_UEFI;

typedef enum {
    HypercallEnvironmentUefi = 1,
    HypercallEnvironmentSmm = 2,
    HypercallEnvironmentRuntime = 3,
} ISTANBUL_HYPERCALL_ENVIRONMENT;

typedef struct {
    UINT64 Rax;
    union {
        UINT64 Environment: 4;
        UINT64 Service: 12;
    };
} ISTANBUL_HYPERCALL;