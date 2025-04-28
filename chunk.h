#ifndef bytecompiler_chunk
#define bytecompiler_chunk

#include "common.h"
#include "memory.h"
#include "value.h"
#include <stdint.h>

typedef enum {
	OP_RETURN,
	OP_CONSTANT,
	OP_CONSTANT_LONG,
	OP_NEGATE,
} OpCode;

typedef struct {
	int capacity, count;
	// The values in code can only be between 0 and 255 which
	// is a constraint for constants as only 255 constants can be stored
	// at max.
	uint8_t* code;
	ValueArray constants;
	int *lines;
	MemoryPool *memoryPool;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void writeConstant(Chunk *chunk, Value value, int line);
void freeChunk(Chunk *chunk);
int addConstant(Chunk *chunk, Value value);

#endif
