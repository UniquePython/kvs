#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdbool.h>
#include <stddef.h>

bool allocate(size_t size, void **out);
void release(void **ptr);

#define Allocate(size, out) allocate((size), (void **)(out))
#define Release(ptr) release((void **)(ptr))

#endif
