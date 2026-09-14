#include "kvs/store.h"
#include "storenode.h"
#include "store.h"
#include "kvs/globalerror.h"
#include "globalerror.h"
#include "kvs/storeerror.h"
#include "storeerror.h"
#include "kvs/type.h"
#include "memory.h"
#include <stddef.h>

bool KvsCreate(KvsStore **out)
{
    if (out == NULL)
        return false;

    KvsStore *store;
    if (!Allocate(sizeof(KvsStore), &store))
    {
        SetGlobalError(KVS_GEC_STORE_ALLOC_FAILED, "Ran out of memory while allocating KvsStore");
        return false;
    }

    store->head = NULL;
    store->size = 0;

    store->error.code = KVS_SEC_NO_ERROR;
    store->error.msg = NULL;

    *out = store;
    return true;
}

void KvsDestroy(KvsStore **ptr)
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

bool KvsSize(const KvsStore *store, size_t *size)
{
    if (store == NULL || size == NULL)
        return false;

    *size = store->size;
    return true;
}

bool KvsHas(const KvsStore *store, KvsType key)
{
    if (store == NULL)
        return false;

    StoreNode *current = store->head;
    while (current != NULL)
    {
        if (KvsTypeEquals(current->entry.key, key))
            return true;

        current = current->next;
    }

    return false;
}

bool KvsGet(const KvsStore *store, KvsType key, KvsType *value)
{
    if (store == NULL || value == NULL)
        return false;

    StoreNode *current = store->head;
    while (current != NULL)
    {
        if (KvsTypeEquals(current->entry.key, key))
        {
            *value = current->entry.value;
            return true;
        }

        current = current->next;
    }

    return false;
}

bool KvsSet(KvsStore *store, KvsType key, KvsType value)
{
    return KvsSetOverwrote(store, key, value, NULL);
}

bool KvsSetOverwrote(KvsStore *store, KvsType key, KvsType value, bool *yes)
{
    if (store == NULL)
        return false;

    if (yes != NULL)
        *yes = false;

    StoreNode *current = store->head;
    StoreNode *previous = NULL;
    while (current != NULL)
    {
        if (KvsTypeEquals(current->entry.key, key))
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
    {
        SetStoreError(store, KVS_SEC_NODE_ALLOC_FAILED, "Ran out of memory while allocating Node to append new entry");
        return false;
    }

    if (previous == NULL)
        store->head = node;
    else
        previous->next = node;

    store->size++;

    return true;
}

bool KvsDelete(KvsStore *store, KvsType key)
{
    if (store == NULL)
        return false;

    StoreNode *previous = NULL;
    StoreNode *current = store->head;

    while (current != NULL)
    {
        if (KvsTypeEquals(current->entry.key, key))
        {
            if (previous == NULL)
                store->head = current->next;
            else
                previous->next = current->next;

            StoreNodeDestroy(&current);
            store->size--;
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}
