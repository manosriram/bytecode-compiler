#ifndef bytecompiler_chunk
#define bytecompiler_chunk

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
	OP_RETURN,
	OP_CONSTANT,
} OpCode;

typedef struct {
	int capacity, count;
	uint8_t* code;
	ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte);
void freeChunk(Chunk *chunk);
int addConstant(Chunk *chunk, Value value);

#endif
