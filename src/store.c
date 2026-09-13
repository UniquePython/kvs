#include "kvs/store.h"
#include "kvs/entry.h"
#include <stddef.h>

typedef struct StoreNode
{
    Entry entry;
    struct StoreNode *next;

} StoreNode;

struct Store
{
    StoreNode *head;
    size_t size;
};
