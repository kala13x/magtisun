/*---------------------------------------------------------------------------

 MagtiSun is commandline application which makes you able to send sms 
 with terminal via magtifun. Also you can implement libmagtisun in 
 another C/C++ application prjects to send sms from your application 
 with or without graphical interface.

 Copyright (c) 2015 Sun Dro (a.k.a. 7th Ghost) & Niko Peikrishvili
 Web: http://off-sec.com/ ; E-Mail: kala0x13@gmail.com

 This is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3 of the License, or (at your option) any later version.

 This software is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

---------------------------------------------------------------------------*/

/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Coockie files */
#define RESPONSE_FILE "/tmp/mslres.log"
#define COOCKIE_LOGIN "cookie-name"
#define COOCKIE_SEND "cookie-name-send"
#define COOCKIE_FILE "cookie"
#define DISCARD_FILE "/dev/null"
#define LOGIN_FILE "/tmp/msl"

/* Version and build number */
#define MSLVERSION "0.1.2 Snapshot"
#define MSLBUILD 22


/*---------------------------------------------
| Structure of user variables
---------------------------------------------*/
typedef struct {
    /* User input */
    char name[128];
    char txt[512];
    char pwd[32];
    char num[16];
    char usr[16];
    short logged;
    int mleft;
} MagtiSunLib;


/*---------------------------------------------
| Get library version
---------------------------------------------*/
const char* msl_get_version();


/*---------------------------------------------
| Handle signals and clean (security reasons)
---------------------------------------------*/
void msl_cleanup(int sig);


/*---------------------------------------------
| Decrypt string (security reasons)
---------------------------------------------*/
char* msl_decrypt(char *str);


/*---------------------------------------------
| Crypt string (security reasons)
---------------------------------------------*/
char* msl_crypt(char *str);


/*---------------------------------------------
| Initialise magtisun login variables
---------------------------------------------*/
void msl_init(MagtiSunLib* msl);


/*---------------------------------------------
| Read login information
---------------------------------------------*/
void msl_cli_init(MagtiSunLib* msl);


/*---------------------------------------------
| Read sms information
---------------------------------------------*/
void msl_init_sms(MagtiSunLib* msl);


/*---------------------------------------------
| Get information about user
---------------------------------------------*/
int msl_get_info(MagtiSunLib* msl);


/*---------------------------------------------
| Create templorary file for login session
---------------------------------------------*/
int msl_login(MagtiSunLib* msl);


/*---------------------------------------------
| Remove templorary file for login session
---------------------------------------------*/
void msl_logout();


/*---------------------------------------------
| Authorise and send sms
---------------------------------------------*/
int msl_send(MagtiSunLib* msl);


/*---------------------------------------------
| For include header in CPP code
---------------------------------------------*/
#ifdef __cplusplus
}
#endif
