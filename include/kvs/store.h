#ifndef KVS_STORE_H_
#define KVS_STORE_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Store Store;

bool KvsCreate(Store **out);
void KvsDestroy(Store **ptr);

bool KvsSize(const Store *store, size_t *size);

#endif
