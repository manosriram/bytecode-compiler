#include "vm.h"
#include "chunk.h"
#include "common.h"
#include "debug.h"
#include <stdint.h>

VM vm;

void resetStack() {
	vm.stackTop = vm.valueStack;
}

Value pop() {
	vm.stackTop--;
	return *vm.stackTop;
}

void push(Value value) {
	*vm.stackTop = value;
	vm.stackTop++;
}

void initVM() {
	resetStack();
}

void freeVM() {}

InterpretResult run() {
	#define READ_BYTE() (*vm.ip++)
	#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

	for (;;) {
		#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value* slot = vm.valueStack; slot < vm.stackTop; slot++) {
      printf("[ ");
      printValue(*slot);
      printf(" ]");
    }
    printf("\n");
		disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
		#endif

		uint8_t instruction;
		switch (instruction = READ_BYTE()) {
			case OP_RETURN:
				printValue(pop());
				return INTERPRET_RESULT_OK;
			case OP_CONSTANT:
				Value constant = READ_CONSTANT();
				push(constant);
				/* printValue(constant); */
				/* printf("\n"); */
				break;
			case OP_CONSTANT_LONG:
				uint8_t byte1 = READ_BYTE();
				uint8_t byte2 = READ_BYTE();
				uint8_t byte3 = READ_BYTE();
				uint32_t reconstructed = ((uint32_t)byte1 << 16) | ((uint32_t)byte2 << 8) | (uint32_t)byte3;
				push(vm.chunk->constants.values[reconstructed]);
				/* printValue(vm.chunk->constants.values[reconstructed]); */
				/* printf("\n"); */
				break;
			case OP_NEGATE:
				push(-pop());
				break;
		}
	}

	#undef READ_BYTE
}

InterpretResult interpret(Chunk *chunk) {
	vm.chunk = chunk;
	vm.ip = vm.chunk->code;

	return run();
}
