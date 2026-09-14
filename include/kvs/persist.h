#ifndef KVS_PERSIST_H_
#define KVS_PERSIST_H_

#include "kvs/store.h"
#include <stdbool.h>

bool KvsSave(const Store *store, const char *path);
bool KvsLoad(const char *path, Store **out);

#endif
