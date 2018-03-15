#include <malloc.h>

void *malloc0(unsigned int size)
{
	nmc_malloc_set_heap(0);
	return malloc(size);
}

void *malloc1(unsigned int size)
{
	nmc_malloc_set_heap(1);
	return malloc(size);
}

void *malloc2(unsigned int size)
{
	nmc_malloc_set_heap(2);
	return malloc(size);
}

void *malloc3(unsigned int size)
{
	nmc_malloc_set_heap(3);
	return malloc(size);
}
