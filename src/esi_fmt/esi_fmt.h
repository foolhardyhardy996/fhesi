#pragma once 

/**
 * @file esi_fmt.h
 * @brief "esi_fmt" provides printf-family that share the same semantics of 
 * standard library 
 * 
 * `sprintf`, `snprintf`, and `vsnprintf` can be used without any additional 
 * assumption. To use `printf`, please implement `_putchar` first. 
 * The signature is `void _putchar(char character)`
 * 
 * @author Li Weida
 * @date 2023.05.31
*/

#include <stdarg.h>
#include <stddef.h>

int esi_printf(const char* format, ...);

int esi_snprintf(char* buffer, size_t count, const char* format, ...);

int esi_vsnprintf(char* buffer, size_t count, const char* format, va_list va);

int esi_vprintf(const char* format, va_list va);

#define esi_fctprintf fctprintf 
int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);
