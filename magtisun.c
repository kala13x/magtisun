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
| Cleanup on exit
---------------------------------------------*/
void cleanup(int sig)
{
    slog(0, "[LIVE] Cleanup on exit");
    remove(COOCKIE_LOGIN);
    remove(COOCKIE_SEND);
    exit(0);
}


/*---------------------------------------------
| Parse cli arguments
---------------------------------------------*/
static int parse_arguments(int argc, char *argv[], MagtiSun_Login* msl)
{
    int c;
    while ( (c = getopt(argc, argv, "u:p:h1")) != -1) {
        switch (c) {
        case 'u':
            strcpy(msl->user, optarg);
            break;
        case 'p':
            strcpy(msl->pwd, optarg);
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
    MagtiSun_Login msl;
    int ret = 0;

    /* Initialise variables */
    init_slog("magtisun", 3);
    init_msl(&msl);

    /* Catch exit signal */
    signal(SIGINT, cleanup);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &msl) < 0) 
    { 
        usage();
        return 0;
    }

    /* Check valid user and password */
    if (strlen(msl.user) < 4 || strlen(msl.pwd) < 4) 
    {
        usage();
        slog(0, "[ERROR] Username and/or Password is not given");
        cli_init_msl(&msl);
    }

    /* Read sms info from user input */
    cli_init_sms(&msl);

    /* Send sms */
    slog(0, "[LIVE] Sending sms...");
    ret = login_and_send(&msl);
    if (ret>=0) slog(0, "[LIVE] Message sent");

    /* Cleanup on exit */
    remove(COOCKIE_LOGIN);
    remove(COOCKIE_SEND);
    return 0;
}