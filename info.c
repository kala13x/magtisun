/*
 * info.c
 * Copyleft (C) 2015  Sun Dro (a.k.a 7th Ghost)
 *
 * Get and print additional information
 */


#include "stdinc.h"
#include "info.h"


/* 
 * Get version. Function returns version and build number of 
 * application. Return value is static char pointer.
 */
const char* get_version()
{
    static char verstr[128];
    sprintf(verstr, "Version %d.%d Build %d (%s)", 
        VERSION_MAX, VERSION_MIN, BUILD, __DATE__);
    return verstr;
}


/*
 * Greet users. Function prints application name, version and
 * build number.
 */
void greet(void) 
{
    printf("====================================================\n");
    printf("MagtiSun-SMS: %s\n", get_version());
    printf("====================================================\n");
} 


/*
 * Print help and usage
 */
void usage(void) 
{
    printf("Usage: magtisun [-l] [-o] [-i] [-h]\n");
    printf("options are:\n");
    printf("   -l                  # do login\n");
    printf("   -o                  # logout from app\n");
    printf("   -i                  # get and print user information\n");
    printf("   -h                  # prints version and usage\n");
    printf("\n");
}
