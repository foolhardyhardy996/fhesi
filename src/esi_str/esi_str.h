#pragma once 

/**
 * @file esi_str.h
 * @brief this module provides common string utility functions from the 
 * standard libc
 * 
 * 
 * 
 * @author Li Weida(modify), Embedded Artistry(original source)
 * @date 2023.5.18
*/

#include <stdint.h>
#include <stdlib.h>

int memcmp(const void* p1, const void* p2, size_t n);
void* memchr(const void* src, int c, size_t n);
void* memcpy(void* dst0, const void* src0, size_t length);
void* memmem(const void* l, size_t l_len, const void* s, size_t s_len);
void* __attribute__((weak)) memmove(void* s1, const void* s2, size_t n);
void* __attribute__((weak)) memset(void* dest, int c, size_t n);
char* strcat(char* __restrict dst, const char* __restrict src);
char* strchr(const char* s, int c);
int strcmp(const char* s1, const char* s2);
char* strcpy(char* __restrict dst, const char* __restrict src);
size_t strcspn(const char* s, const char* c);
size_t strlen(const char* str);
char* strncat(char* __restrict dst, const char* __restrict src, size_t maxlen);
int strncmp(const char* s1, const char* s2, size_t n);
char* strncpy(char* __restrict dst, const char* __restrict src, size_t maxlen);
size_t strnlen(const char* str, size_t maxlen);
char* strnstr(const char* s, const char* find, size_t slen);
char* strpbrk(const char* s, const char* b);
char* strrchr(const char* s, int c);
size_t strspn(const char* s, const char* c);
char* strstr(const char* string, const char* substring);
char* strtok(char* s, const char* delim);

