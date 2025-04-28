#ifndef bytecompiler_memory

#define bytecompiler_memory
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define GROW_CAPACTITY(capacity) \
	((capacity < 8) ? 8 : capacity * 2)


#define GROW_ARRAY(type, pointer, memoryPool, oldCount, newCount) \
	(type*)reallocateFromMemoryPool(pointer, memoryPool, sizeof(type) * (oldCount), \
			sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, memoryPool, oldCount) \
	reallocateFromMemoryPool(pointer, memoryPool, sizeof(type) * (oldCount), 0)

typedef struct MemoryPool {
	int size;
	int capacity;
	void *memory;
} MemoryPool;

MemoryPool *initMemoryPool(int capacity);
void *allocate(MemoryPool *memoryPool, size_t size);
void *reallocateFromMemoryPool(void *pointer, MemoryPool *memoryPool, size_t oldSize, size_t newSize);

void* reallocate(void *pointer, MemoryPool *memoryPool, size_t oldSize, size_t newSize);

#endif
