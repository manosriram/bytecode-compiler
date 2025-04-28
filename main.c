#include "chunk.h"
#include "debug.h"
#include "vm.h"
#include <stdlib.h>
#include <stdio.h>

/*
	1. Create a dynamic sizable array data-structure
	2. Store list of byte sized bytecodes in that list
	3. Create RETURN_OP and CONSTANT_OP and add respective handling <OPCODE> ...

	RETURN_OP takes 1 byte RETURN_OP
	CONSTANT_OP takes 2 bytes CONSTANT_OP <CONSTANT>

	256 -> 0 0 0 0 0 0 0 0

	uint32_t x = 1031;
	uint32_t x1 = x >> 16 & 0xFF;
	uint32_t x2 = x >> 8 & 0xFF;
	uint32_t x3 = x & 0xFF;

	uint32_t reconstructed = (((uint32_t)x1 << 16) | ((uint32_t)x2 << 8) | (uint32_t)x3);
	printf("%u %u %u %d\n", x1, x2, x3, reconstructed);


	function declarations are in *.h files
	function definitions are in *.c files
*/

int main() {
	Chunk chunk;
	initChunk(&chunk);
	initVM();

	writeChunk(&chunk, OP_CONSTANT, 1);
	writeChunk(&chunk, addConstant(&chunk, 1.4), 1);

	writeChunk(&chunk, OP_CONSTANT_LONG, 1);
	writeConstant(&chunk, 555, 1);

	writeChunk(&chunk, OP_NEGATE, 1);

	/* for (int t=0;t<799;t++) { */
		/* writeChunk(&chunk, OP_CONSTANT_LONG, 1); */
		/* writeConstant(&chunk, t, 1); */
	/* } */

	writeChunk(&chunk, OP_RETURN, 1);

	/* disassembleChunk(&chunk, "test opcode"); */

	interpret(&chunk);

	freeChunk(&chunk);
	freeVM();

	return 0;
}
