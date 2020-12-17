
#include "../shodan.h"

/**********/
void* Calloc(size_t count, size_t size)
{
	void* p = calloc(count, size);

	if (p == NULL) { Error(__func__, "Allocation failed"); };

	return p;
}

/**********/
void* Malloc(size_t size)
{
	void* p = malloc(size);

	if (p == NULL) { Error(__func__, "Allocation failed"); };

	return p;
}

/**********/
void* Realloc(void* ptr, size_t size)
{
	void* p = realloc(ptr, size);

	if (p == NULL) { Error(__func__, "Allocation failed"); };

	return p;
}

/**********/
void Free(void* p)
{
	if (p != NULL) { free(p); };
}

