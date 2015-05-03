/*-----------------------------------------------------
Name: info.h
Date: 2015.05.03
Auth: kala13x (a.k.a 7th Ghost)
Desc: Get and print additional information
-----------------------------------------------------*/

#include "stdinc.h"

/* Version and build number */
#define VERSION "0.0.1 Beta"
#define BUILD 2


/*---------------------------------------------
| Get application version
---------------------------------------------*/
const char* get_version();


/*---------------------------------------------
| Greet users
---------------------------------------------*/
void greet(void);


/*---------------------------------------------
| Print usage
---------------------------------------------*/
void usage(void);
