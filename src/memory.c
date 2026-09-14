#include "memory.h"
#include <stdlib.h>

bool allocate(size_t size, void **out)
{
    if (size == 0 || out == NULL)
        return false;

    void *ptr = malloc(size);
    if (ptr == NULL)
        return false;

    *out = ptr;
    return true;
}

void release(void **ptr)
{
    if (ptr == NULL || *ptr == NULL)
        return;

    free(*ptr);
    *ptr = NULL;
}
