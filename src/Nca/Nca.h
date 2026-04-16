#ifndef CLANG_SAL_H
#define CLANG_SAL_H

#if !defined(__clang__)
#error "Nca.h only supports clang"
#else

#define _In_            _Nonnull
#define _In_opt_        _Nullable
#define _Out_           _Nonnull
#define _Out_opt_       _Nullable
#define _Inout_         _Nonnull
#define _Inout_opt_     _Nullable
#define _Verify_(cond)	__builtin_assume(cond)
#define _Unused_var_(v) (void)v

#define _Out_writes_(size_idx) \
        __attribute__((pass_dynamic_object_size(0)))
#define _In_reads_(size_idx) \
    __attribute__((diagnose_if(!__builtin_constant_p(size_idx), "Non-constant size", "warning")))

#define _Field_size_(count)      __attribute__((counted_by(count)))
#define _Field_size_opt_(count)  __attribute__((counted_by_or_null(count)))
#define _Field_bytes_(size)      __attribute__((sized_by(size)))
#define _Field_bytes_opt_(size)  __attribute__((sized_by_or_null(size)))
#define _Packed_                 __attribute__((packed))

#define _Check_return_  __attribute__((warn_unused_result))
#define _No_return_     __attribute__((noreturn))
#define _Deprecated_    __attribute__((deprecated))
#define _Pure_          __attribute__((pure))
#define _Hot_           __attribute__((hot))
#define _Cold_          __attribute__((cold))

#define _Ret_malloc_    __attribute__((malloc))
#define _Aligned_(n)    __attribute__((assume_aligned(n)))

#define _Guarded_by_(x)   	__attribute__((guarded_by(x)))
#define _Requires_lock_(x) 	__attribute__((requires_capability(x)))
#define _Acquires_lock_(x) 	__attribute__((acquire_capability(x)))
#define _Releases_lock_(x) 	__attribute__((release_capability(x)))
#define _Locks_excluded_(x) 	__attribute__((locks_excluded(x)))
#define _Lockable_ 		__attribute((capability("mutex")))
#define _Printf_format_(fmt_idx, dot_idx) __attribute__((format(printf, fmt_idx, dot_idx)))

#define _No_inline_     __attribute__((noinline))
#define _Always_inline_ __attribute__((always_inline))
#define _Maybe_unused_  __attribute__((unused))

#endif // __clang__
#endif // CLANG_SAL_H
