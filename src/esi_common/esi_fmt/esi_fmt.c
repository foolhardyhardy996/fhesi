#include <stdarg.h>

#include "printf.h"
#include "esi_fmt.h"

int esi_printf(const char* format, ...) {
    va_list va;
    int ret;

    va_start(va, format);
    ret = vprintf_(format, va);
    va_end(va);

    return ret;
}

int esi_snprintf(char* buffer, size_t count, const char* format, ...) {
    va_list va;
    int ret;

    va_start(va, format);
    ret = snprintf_(buffer, count, format, va);
    va_end(va);

    return ret;
}

int esi_vsnprintf(char* buffer, size_t count, const char* format, va_list va) {
    return vsnprintf_(buffer, count, format, va);
}

int esi_vprintf(const char* format, va_list va) {
    return vprintf_(format, va);
}
