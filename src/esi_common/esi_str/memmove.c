#include <stddef.h>
#include "esi_str.h"

void* __attribute__((weak)) memmove(void* s1, const void* s2, size_t n)
{
	return memcpy(s1, s2, n);
}
