#ifndef bytecompiler_value
#define bytecompiler_value

#include "common.h"
#include <stdint.h>

typedef double Value;

typedef struct {
	int capacity, count;
	Value *values;
} ValueArray;

void initValueArray(ValueArray *value);
void writeValueArray(ValueArray *value, Value values);
void freeValueArray(ValueArray *value);

#endif
