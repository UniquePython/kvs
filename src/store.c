#include "kvs/store.h"
#include "storenode.h"
#include "store.h"
#include "kvs/type.h"
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
    Release(ptr);
}

bool KvsSize(const Store *store, size_t *size)
{
    if (store == NULL || size == NULL)
        return false;

    *size = store->size;
    return true;
}

bool KvsHas(const Store *store, Type key)
{
    if (store == NULL)
        return false;

    StoreNode *current = store->head;
    while (current != NULL)
    {
        if (TypeEquals(current->entry.key, key))
            return true;

        current = current->next;
    }

    return false;
}

bool KvsGet(const Store *store, Type key, Type *value)
{
    if (store == NULL || value == NULL)
        return false;

    StoreNode *current = store->head;
    while (current != NULL)
    {
        if (TypeEquals(current->entry.key, key))
        {
            *value = current->entry.value;
            return true;
        }

        current = current->next;
    }

    return false;
}
