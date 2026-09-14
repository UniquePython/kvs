#ifndef KVS_STORE_H_
#define KVS_STORE_H_

#include "kvs/type.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct Store Store;

bool KvsCreate(Store **out);
void KvsDestroy(Store **ptr);

bool KvsSize(const Store *store, size_t *size);

bool KvsHas(const Store *store, Type key);
bool KvsGet(const Store *store, Type key, Type *value);

bool KvsSet(Store *store, Type key, Type value);
bool KvsSetOverwrote(Store *store, Type key, Type value, bool *yes);

bool KvsDelete(Store *store, Type key);

#endif
