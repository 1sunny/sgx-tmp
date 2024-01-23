
#include <stdarg.h>
#include <stdio.h> /* vsnprintf */
#include <string.h>

char result[2][1000]={0};
int print_xgroup(int flag, const char* fmt, ...)
{
    char buf[BUFSIZ] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    strncat(result[flag], buf, strlen(buf));
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}

void print_all(int flag, FILE* file) {
    fputs(result[flag], file);
    result[flag][0] = 0;
}