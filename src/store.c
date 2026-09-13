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
    if (ptr == NULL || *ptr == NULL)
        return;

    StoreNode *current = (*ptr)->head;
    while (current != NULL)
    {
        StoreNode *next = current->next;
        StoreNodeDestroy(&current);
        current = next;
    }

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

bool KvsSet(Store *store, Type key, Type value)
{
    return KvsSetOverwrote(store, key, value, NULL);
}

bool KvsSetOverwrote(Store *store, Type key, Type value, bool *yes)
{
    if (store == NULL)
        return false;

    if (yes != NULL)
        *yes = false;

    StoreNode *current = store->head;
    StoreNode *previous = NULL;
    while (current != NULL)
    {
        if (TypeEquals(current->entry.key, key))
        {
            current->entry.value = value;
            if (yes != NULL)
                *yes = true;
            return true;
        }

        previous = current;
        current = current->next;
    }

    StoreNode *node;
    if (!StoreNodeCreate(key, value, &node))
        return false;

    if (previous == NULL)
        store->head = node;
    else
        previous->next = node;

    return true;
}
