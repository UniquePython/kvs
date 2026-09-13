#ifndef KVS_STORE_H_
#define KVS_STORE_H_

#include <stdbool.h>

typedef struct Store Store;

bool KvsCreate(Store **out);
void KvsDestroy(Store **ptr);

#endif
