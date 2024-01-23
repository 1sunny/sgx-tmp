// #include "Enclave.h"
#include "Enclave_t.h" /* print_string */
#include <stdarg.h>
#include <stdio.h> /* vsnprintf */
#include <string.h>

char result[1000]={0};
int print_group(const char* fmt, ...)
{
    char buf[BUFSIZ] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    strncat(result, buf, strlen(buf));
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

void print_all() {
    ocall_print_all_group(result);
    result[0] = 0;
}