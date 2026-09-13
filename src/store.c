#include "kvs/store.h"
#include "store.h"
#include "memory.h"
#include <stddef.h>

bool KvsCreate(Store **out)
{
    if (out == NULL)
        return false;

    Store *store;
    if (!Allocate(sizeof(Store), &store))
        return false;

    store->head = NULL;
    store->size = 0;

    *out = store;
    return true;
}

void KvsDestroy(Store **ptr)
{
    if (ptr == NULL || *ptr == NULL)
        return;

    (*ptr)->head = NULL;
    (*ptr)->size = 0;

    Release(ptr);
}
