#ifndef MALLOC32_DEFINED
#define MALLOC32_DEFINED

#define HEAP_0 1
#define HEAP_1 2
#define HEAP_2 4
#define HEAP_3 8

void* malloc32 (unsigned size_int32 );
void* malloc32 (unsigned size_int32, unsigned bank_mask);
void  free32(void* p);

typedef void (*t_free_func)(void*);

#endif
