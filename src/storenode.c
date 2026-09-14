#include "storenode.h"
#include "memory.h"

bool StoreNodeCreate(KvsType key, KvsType value, StoreNode **out)
{
    if (out == NULL)
        return false;

    StoreNode *node;
    if (!Allocate(sizeof(StoreNode), &node))
        return false;

    node->entry.key = key;
    node->entry.value = value;
    node->next = NULL;

    *out = node;
    return true;
}

void StoreNodeDestroy(StoreNode **ptr)
{
    Release(ptr);
}
