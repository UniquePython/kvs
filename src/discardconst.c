#include "discardconst.h"
#include <stdint.h>

// Deliberately discards const. Only ever safe to call on an object that was
// never actually declared const in the first place (e.g. a KvsStore, always
// heap-allocated as non-const) -- it exists so functions that take a
// const-qualified pointer for a genuine, honest reason (they don't touch the
// object's real data) can still record bookkeeping like a last-error slot,
// which we consider outside what that const promise covers.
//
// The uintptr_t roundtrip is intentional: a direct pointer-to-pointer cast
// here would trip -Wcast-qual, which we want on everywhere else in this
// codebase. This is the one sanctioned exception, and it lives in exactly
// one place so it stays visible instead of being repeated ad hoc.
void *discardConst(const void *ptr)
{
    uintptr_t addr = (uintptr_t)ptr;
    return (void *)addr;
}
