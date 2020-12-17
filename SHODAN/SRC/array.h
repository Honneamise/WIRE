#ifndef ARRAY_H
#define ARRAY_H

#define _DEFAULT_ARRAY_DIM 32

//array
typedef struct SArray
{
	int dim;
	int size;
	void** items;

} SArray;

/**********/
SArray* ArrayInit();

void ArrayClose(SArray** array);

void ArrayAdd(SArray* array, void* item);

void* ArrayGet(SArray* array, int index);

void* ArrayRemove(SArray* array, int index);

#endif