# kvs

**kvs** stands for **Key-Value Store**, which is a simple *database* that can be used for storing *values* associated
with some *key*

## Status

Versioned under [BFIP Versioning](https://github.com/UniquePython/bfip-versioning), currently
at `0.1.0.0` (breaking version zero, no public API stability promise yet). See
[CONTRIBUTING.md](CONTRIBUTING.md) for the versioning and branching model.

## `0.1.0.0` API

### Types

- `Type`: a tagged union holding one of four fixed-width unsigned integers:
  `TK_U8`, `TK_U16`, `TK_U32`, `TK_U64`.
- `Store`: opaque. A key-value store, currently backed by a linked list.
- `KvsIterator`: opaque. A cursor over a `Store`'s entries.

### `Type`

```c
Type TypeU8(uint8_t value);
Type TypeU16(uint16_t value);
Type TypeU32(uint32_t value);
Type TypeU64(uint64_t value);

bool TypeEquals(Type a, Type b);
bool TypePrint(Type type, FILE *stream);

const char *TypeKindName(TypeKind kind);
```

### `Store`

```c
bool KvsCreate(Store **out);
void KvsDestroy(Store **ptr);

bool KvsSize(const Store *store, size_t *size);

bool KvsHas(const Store *store, Type key);
bool KvsGet(const Store *store, Type key, Type *value);

bool KvsSet(Store *store, Type key, Type value);
bool KvsSetOverwrote(Store *store, Type key, Type value, bool *yes);

bool KvsDelete(Store *store, Type key);
```

### Iteration

```c
bool KvsIterCreate(const Store *store, KvsIterator **out);
bool KvsIterNext(KvsIterator *it, Type *key, Type *value);
void KvsIterDestroy(KvsIterator **ptr);

bool KvsForEach(const Store *store, KvsForEachFn fn, void *ctx);
```

> Mutating a store while an iterator over it is live is undefined behavior.

### Persistence

```c
bool KvsSave(const Store *store, const char *path);
bool KvsLoad(const char *path, Store **out);
```

Saves are atomic and portable across machine architectures (values are stored big-endian on disk
regardless of host byte order).
