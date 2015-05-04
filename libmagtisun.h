/*---------------------------------------------------------------------------

 MagtiSun is commandline application which makes you able to send sms
 with terminal via magtifun sms api. You also can implement libmagtisun 
 in another cli applications to send sms with terminal.

 Copyright (c) 2015 Sun Dro (a.k.a. 7th Ghost)
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

#include "stdinc.h"

/* Coockies files */
#define COOCKIE_LOGIN "cookie-name"
#define COOCKIE_SEND "cookie-name-send"
#define COOCKIE_FILE "cookie"
#define DISCARD_FILE "/dev/null"
#define LOGIN_FILE "/tmp/msl"
#define SAVE_FILE "response"


/*---------------------------------------------
| Structure of user variables
---------------------------------------------*/
typedef struct {
    char* res;
    char* pwd;
    char txt[512];
    char num[16];
    char user[16];
    short info;
    short login;
} MagtiSunLib;


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
| Authorise and send sms
---------------------------------------------*/
int msl_send(MagtiSunLib* msl);