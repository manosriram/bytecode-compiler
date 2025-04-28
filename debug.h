#ifndef bytecompiler_debug

#define bytecompiler_debug
#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);
void printValue(Value value);
static int constantLongInstruction(Chunk *chunk, const char *instructionName, int offset);

#endif
