/*
 * info.c
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and print additional information
 */


#include "stdinc.h"

/* Version and build number */
#define VERSION_MAX 1
#define VERSION_MIN 0
#define BUILD 34


/* 
 * Get version. Function returns version and build number of 
 * application. Return value is static char pointer.
 */
const char* get_version();


/*
 * Greet users. Function prints application name, version and
 * build number.
 */
void greet(void);


/*
 * Print help and usage
 */
void usage(void);
