#ifndef DISCARDCONST_H_
#define DISCARDCONST_H_

void *discardConst(const void *ptr);

#define DiscardConst(ptr) discardConst((const void *)(ptr))

#endif
