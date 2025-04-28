#include <stdlib.h>
#include "memory.h"

MemoryPool *initMemoryPool(int capacity) {
	MemoryPool *m = (MemoryPool *)malloc(sizeof(MemoryPool));
	m->capacity = capacity;
	m->size = 0;
	m->memory = malloc(m->capacity);
	return m;
}

void *reallocate(void *pointer, MemoryPool *memoryPool, size_t oldSize, size_t newSize) {
	if (newSize == 0) {
		free(pointer);
		return NULL;
	}

	void *result = realloc(pointer, newSize);
	if (result == NULL) exit(1);
	return result;
}

void *reallocateFromMemoryPool(void *pointer, MemoryPool *memoryPool, size_t oldSize, size_t newSize) {
	if (newSize == 0) {
		free(pointer);
		return NULL;
	}

	free(pointer);
	return allocate(memoryPool, newSize);
}

void *allocate(MemoryPool *memoryPool, size_t size) {
	if (memoryPool->size >= memoryPool->capacity || memoryPool->size + size > memoryPool->capacity) {
		return NULL;
	}

	void *p = &memoryPool->memory[memoryPool->size];
	if (p == NULL) exit(1);
	memoryPool->size += size;
	return p;
}

