#include "value.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void initValueArray(ValueArray *array) {
	array->capacity = 0;
	array->count = 0;
	array->values = NULL;
	array->memoryPool = initMemoryPool(90000);
}

void writeValueArray(ValueArray *array, Value values) {
	if (array->capacity < array->count + 1) {
		int oldCapacity = array->capacity;
		array->capacity = GROW_CAPACTITY(oldCapacity);
		array->values = GROW_ARRAY(Value, array->values, array->memoryPool, oldCapacity, array->capacity);
	}

	array->values[array->count] = values;
	array->count++;
}

void freeValueArray(ValueArray *value) {
	free(value->memoryPool);
	/* FREE_ARRAY(Value, value->values, value->memoryPool, value->capacity); */
	initValueArray(value);
}
