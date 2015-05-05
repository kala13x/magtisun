/*---------------------------------------------------------------------------

 MagtiSun is commandline application which makes you able to send sms 
 with terminal via magtifun. Also you can implement libmagtisun in 
 another C/C++ application prjects to send sms from your application 
 with or without graphical interface.

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


#include "libmagtisun.h"
#include "stdinc.h"
#include "slog.h"
#include "info.h"


/*---------------------------------------------
| Read login information
---------------------------------------------*/
void init_info(MagtiSunLib* msl) 
{
    /* Get username */
    printf(ret_slog("[INPUT] Enter Username: "));
    scanf("%s", msl->usr);

    /* Get password (invisible) */
    char* pwd = getpass(ret_slog("[INPUT] Enter Password: "));
    strcpy(msl->pwd, pwd);
}


/*---------------------------------------------
| Read sms information
---------------------------------------------*/
void init_sms(MagtiSunLib* msl)
{
    /* Get number */
    printf(ret_slog("[INPUT] Enter Number: "));
    scanf("%s", msl->num);

    /* Get sms text */
    printf(ret_slog("[INPUT] Enter Text: "));
    scanf("%s", msl->txt);
}


/*---------------------------------------------
| Parse cli arguments
---------------------------------------------*/
static int parse_arguments(int argc, char *argv[], MagtiSunLib* msl)
{
    int c;
    while ( (c = getopt(argc, argv, "l1:o1:i1:h1")) != -1) {
        switch (c) {
        case 'l':
            msl->login = 1;
            break;
        case 'o':
            slog(0, "[LIVE] Logging out");
            msl_logout();
            break;
        case 'i':
            msl->info = 1;
            break;
        case 'h':
        default:
            return -1;
        }
    }

    return 0;
}


/*---------------------------------------------
| Main function
---------------------------------------------*/
int main(int argc, char **argv)
{
    /* Used variables */
    MagtiSunLib msl;
    int ret = 0;

    /* Greet users */
    greet();

    /* Initialise variables */
    init_slog("magtisun", 3);
    msl_init(&msl);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &msl) < 0) 
    { 
        usage();
        return 0;
    }

    /* Log in user */
    if (msl.login)
    {
        if(msl_login(&msl)) 
            slog(0, "[LIVE] Logged in");
    }

    /* Check valid user */
    if (strlen(msl.usr) < 4 && strlen(msl.pwd) < 4) 
    {
        slog(0, "[LIVE] Not logged in");
        init_info(&msl);
    }

    /* Check logged in user */
    if (msl.logged) 
        slog(0, "[LIVE] Logged in as: %s", msl.usr);

    /* Check info */
    if (msl.info) msl_get_info(&msl);

    /* Read sms info from user input */
    init_sms(&msl);

    /* Send sms */
    slog(0, "[LIVE] Sending message...");
    ret = msl_send(&msl);
    if (ret>=0) slog(0, "[LIVE] Message sent");
    else 
    {
        slog(0, "[ERROR] Can not send sms");
        slog(0, "[INFO] The reason can be wrong username and/or password");
        slog(0, "[INFO] Also make sure you can ping magtifun.ge");
    }

    return 0;
}