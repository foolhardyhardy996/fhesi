// Imported from musl Libc

#include "esi_str.h"
#include "strchrnul.h"

char* strchr(const char* s, int c)
{
	char* r = __strchrnul(s, c);
	return *(unsigned char*)r == (unsigned char)c ? r : 0;
}
