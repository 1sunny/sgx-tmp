#include "config.h"

#ident "$Id$"

#include "alloc.h"

// #include <errno.h>
#include <stddef.h>
// #include <stdio.h>

// #include "defines.h"
#include "prototypes.h"
// #include "shadowlog.h"


extern inline void *xmalloc(size_t size);
extern inline void *xmallocarray(size_t nmemb, size_t size);
extern inline void *mallocarray(size_t nmemb, size_t size);
extern inline void *reallocarrayf(void *p, size_t nmemb, size_t size);
extern inline char *xstrdup(const char *str);


void *
xcalloc(size_t nmemb, size_t size)
{
	void  *p;

	p = calloc(nmemb, size);
	// if (p == NULL)
	// 	goto x;

	return p;

// x:
	// fprintf(log_get_logfd(), _("%s: %s\n"),
	//         log_get_progname(), strerror(errno));
	// exit(13);
}


void *
xreallocarray(void *p, size_t nmemb, size_t size)
{
	p = reallocarrayf(p, nmemb, size);
	// if (p == NULL)
	// 	goto x;

	return p;

// x:
	// fprintf(log_get_logfd(), _("%s: %s\n"),
	//         log_get_progname(), strerror(errno));
	// exit(13);
}


void *reallocarray(void *__ptr, size_t __nmemb, size_t __size) {
    // Check for integer overflow in the size calculation
    if (__nmemb && SIZE_MAX / __nmemb < __size) {
        // Overflow occurred
        return NULL;
    }

    size_t new_size = __nmemb * __size;

    // Reallocate memory
    void *new_ptr = realloc(__ptr, new_size);

    return new_ptr;
}