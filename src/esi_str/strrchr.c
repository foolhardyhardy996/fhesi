// Imported from musl Libc

#include "esi_str.h"

void* __memrchr(const void*, int, size_t);

void* __memrchr(const void* m, int c, size_t n)
{
	const unsigned char* s = m;
	c = (unsigned char)c;

	while(n--)
	{
		if(s[n] == c)
		{
			return (void*)(uintptr_t)(s + n);
		}
	}

	return 0;
}


char* strrchr(const char* s, int c)
{
	return __memrchr(s, c, strlen(s) + 1);
}
