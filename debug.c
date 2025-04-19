#include "debug.h"
#include "chunk.h"
#include <stdint.h>
#include <stdio.h>

static int constantInstruction(Chunk *chunk, const char *instructionName, int offset) {
	printf("%s %d\n", instructionName, chunk->code[offset+1]);
	return offset + 2;
}

static int simpleInstruction(const char *instructionName, int offset) {
	printf("%s\n", instructionName);
	return offset + 1;
}

void disassembleChunk(Chunk *chunk, const char *name) {
	printf("== %s ==\n", name);
	for (int offset = 0;offset < chunk->count;) {
		offset = disassembleInstruction(chunk, offset);
	}
}

int disassembleInstruction(Chunk *chunk, int offset) {
	printf("%04d ", offset);

	uint8_t instruction = chunk->code[offset];
	switch (instruction) {
		case OP_RETURN:
			return simpleInstruction("OP_RETURN", offset);
		case OP_CONSTANT:
			return constantInstruction(chunk, "OP_CONSTANT", offset);
		default:
		printf("Unknown Opcode\n");
		return offset + 1;
	}
}
