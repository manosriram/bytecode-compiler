#include "chunk.h"
#include "debug.h"

/*
	1. Create a dynamic sizable array data-structure
	2. Store list of byte sized bytecodes in that list
	3. Create RETURN_OP and CONSTANT_OP and add respective handling <OPCODE> ...

	RETURN_OP takes 1 byte RETURN_OP
	CONSTANT_OP takes 2 bytes CONSTANT_OP <CONSTANT>



	function declarations are in *.h files
	function definitions are in *.c files
*/

int main() {
	Chunk chunk;
	initChunk(&chunk);
	writeChunk(&chunk, OP_RETURN);

	writeChunk(&chunk, OP_CONSTANT);
	writeChunk(&chunk, addConstant(&chunk, 1.2));

	disassembleChunk(&chunk, "test opcode");

	freeChunk(&chunk);

	return 0;
}
