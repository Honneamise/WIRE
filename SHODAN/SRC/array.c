
#include "../shodan.h"

/*********/
SArray* ArrayInit()
{
	SArray* array = Calloc(1, sizeof(SArray));

	array->size = 0;
	array->dim = _DEFAULT_ARRAY_DIM;
	array->items = Calloc(_DEFAULT_ARRAY_DIM, sizeof(void*));

	return array;
}

/*********/
void ArrayClose(SArray** array)
{
	Free((*array)->items);

	Free(*array);

	*array = NULL;
}

/*********/
void ArrayAdd(SArray* array, void* item)
{
	if (array->size == array->dim)
	{
		array->dim += _DEFAULT_ARRAY_DIM;
		array->items = Realloc(array->items, array->dim * sizeof(void*));
	}

	array->items[array->size] = item;

	array->size++;
}

/*********/
void* ArrayGet(SArray* array, int index)
{
	if (index >= array->size) { Log(__func__, "Index out of range"); return NULL; };

	return array->items[index];
}

/*********/
void* ArrayRemove(SArray* array, int index)
{
	if (index >= array->size) { Log(__func__, "Index out of range"); return NULL; };

	void* item = array->items[index];

	for (int i = index; i < array->size - 1; i++)
	{
		array->items[i] = array->items[i + 1];
	}

	array->size--;

	return item;
}

