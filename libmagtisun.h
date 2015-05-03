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
#define COOCKIE_FILE "cookie.tmp"

/*---------------------------------------------
| Structure of user variables
---------------------------------------------*/
typedef struct {
    char txt[512];
    char num[16];
    char* user;
    char* pwd;
} MagtiSun_Login;


/*---------------------------------------------
| Initialise magtisun login variables
---------------------------------------------*/
void init_msl(MagtiSun_Login* msl);


/*---------------------------------------------
| Read login information
---------------------------------------------*/
void cli_init_msl(MagtiSun_Login* msl);


/*---------------------------------------------
| Read sms information
---------------------------------------------*/
void cli_init_sms(MagtiSun_Login* msl);


/*---------------------------------------------
| Get authorisation at magtifun
---------------------------------------------*/
int make_login(char *user, char* pwd);


/*---------------------------------------------
| Send sms with magtifun
---------------------------------------------*/
int send_sms(char *num, char* txt);


/*---------------------------------------------
| Authorise and send sms
---------------------------------------------*/
int login_and_send(MagtiSun_Login* msl);