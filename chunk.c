#include "chunk.h"
#include "memory.h"
#include "value.h"
#include <stdint.h>
#include <stdio.h>

void initChunk(Chunk *chunk) {
	chunk->capacity = 0;
	chunk->count = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	initValueArray(&chunk->constants);
}

// 3 byte extension for constants
// write the value in form of 3 divided bytes
void writeConstant(Chunk *chunk, Value value, int line) {
	int idx = addConstant(chunk, value);
	uint8_t byte1 = (idx >> 16) & 0xFF;
	uint8_t byte2 = (idx >> 8) & 0xFF;
	uint8_t byte3 = idx & 0xFF;

	writeChunk(chunk, byte1, line);
	writeChunk(chunk, byte2, line);
	writeChunk(chunk, byte3, line);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACTITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
		chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

void freeChunk(Chunk *chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);

    return chunk->constants.count - 1;
}
