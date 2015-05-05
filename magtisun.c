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


#include "libmagtisun.h"
#include "stdinc.h"
#include "slog.h"
#include "info.h"


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
        msl_cli_init(&msl);
    }

    /* Check logged in user */
    if (msl.logged) 
        slog(0, "[LIVE] Logged in as: %s", msl.usr);

    /* Check info */
    if (msl.info) msl_get_info(&msl);

    /* Read sms info from user input */
    msl_init_sms(&msl);

    /* Send sms */
    slog(0, "[LIVE] Sending message...");
    ret = msl_send(&msl);
    if (ret>=0) slog(0, "[LIVE] Message sent");
    else slog(0, "[ERROR] Can not send sms");

    return 0;
}