#ifndef STD_H
#define STD_H

//std
void* Calloc(size_t count, size_t size);

void* Malloc(size_t size);

void* Realloc(void* ptr, size_t size);

void Free(void* p);

#endif