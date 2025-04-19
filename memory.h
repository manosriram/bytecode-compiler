#ifndef bytecompiler_memory

#define bytecompiler_memory
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define GROW_CAPACTITY(capacity) \
	((capacity < 8) ? 8 : capacity * 2)


#define GROW_ARRAY(type, pointer, oldCount, newCount) \
	(type*)reallocate(pointer, sizeof(type) * (oldCount), \
			sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
	reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
