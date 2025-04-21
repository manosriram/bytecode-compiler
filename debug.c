#include "debug.h"
#include "chunk.h"
#include <stdint.h>
#include <stdio.h>

static int constantLongInstruction(Chunk *chunk, const char *instructionName, int offset) {
	uint8_t byte1 = chunk->code[offset + 1];
	uint8_t byte2 = chunk->code[offset + 2];
	uint8_t byte3 = chunk->code[offset + 3];
	uint32_t reconstructed = ((uint32_t)byte1 << 16) | ((uint32_t)byte2 << 8) | (uint32_t)byte3;

	/* // %-16s: Left-aligned instruction name with 16 char width */
	/* // %4d: Right-aligned constant index with 4 char width */
	printf("%-16s %4d '", instructionName, reconstructed);
	printValue(chunk->constants.values[reconstructed]);
	printf("'\n");
	return offset + 4;
}

static int constantInstruction(Chunk *chunk, const char *instructionName, int offset) {
	uint8_t constant = chunk->code[offset + 1];
	// %-16s: Left-aligned instruction name with 16 char width
	// %4d: Right-aligned constant index with 4 char width
	printf("%-16s %4d '", instructionName, constant);
	printValue(chunk->constants.values[constant]);
	printf("'\n");
	return offset + 2;
}

static int simpleInstruction(const char *instructionName, int offset) {
	printf("%s \n", instructionName);
	return offset + 1;
}

void disassembleChunk(Chunk *chunk, const char *name) {
	printf("== %s ==\n", name);
	for (int offset = 0;offset < chunk->count;) {
		offset = disassembleInstruction(chunk, offset);
	}
}

int disassembleInstruction(Chunk *chunk, int offset) {
	// %04d: Right-aligned offset with zero padding to 4 digits
	printf("%04d ", offset);
	if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
		printf("\t| ");
	} else {
		printf("%4d ", chunk->lines[offset]);
	}

	uint8_t instruction = chunk->code[offset];
	switch (instruction) {
		case OP_RETURN:
			return simpleInstruction("OP_RETURN", offset);
		case OP_CONSTANT:
			return constantInstruction(chunk, "OP_CONSTANT", offset);
		case OP_CONSTANT_LONG:
			return constantLongInstruction(chunk, "OP_CONSTANT_LONG", offset);
		default:
		printf("Unknown Opcode\n");
		return offset + 1;
	}
}

void printValue(Value value) {
	// %g: Print float/double in shortest form (1.4 instead of 1.400000)
	printf("%g", value);
}
