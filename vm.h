#ifndef bytecompiler_vm

#include "chunk.h"

#define STACK_MAX 256

typedef struct {
	Chunk *chunk;
	uint8_t *ip;

	Value valueStack[STACK_MAX];
	Value *stackTop;
} VM;

typedef enum {
	INTERPRET_RESULT_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk *chunk);
InterpretResult run();
void push(Value value);
Value pop();

#endif
