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
| Handle signals and clean (security reasons)
---------------------------------------------*/
void cleanup(int sig)
{
    /* Handle signals */
    if (sig == SIGILL || sig == SIGSEGV) 
        slog(0, "[ERROR] Incorrect inputed data\n");

    /* Make clean */
    slog(0, "[LIVE] Cleanup on exit\n");
    remove(COOCKIE_LOGIN);
    remove(COOCKIE_SEND);
    remove(SAVE_FILE);
    exit(0);
}


/*---------------------------------------------
| Parse cli arguments
---------------------------------------------*/
static int parse_arguments(int argc, char *argv[], MagtiSun_Login* msl)
{
    int c;
    while ( (c = getopt(argc, argv, "u:p:i1:h1")) != -1) {
        switch (c) {
        case 'u':
            strcpy(msl->user, optarg);
            break;
        case 'p':
            msl->pwd = strdup(optarg);
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
    MagtiSun_Login msl;
    int ret = 0;

    /* Greet users */
    greet();

    /* Initialise variables */
    init_slog("magtisun", 3);
    init_msl(&msl);

    /* Catch ilegal signal */
    signal(SIGINT, cleanup);
    signal(SIGSEGV, cleanup);
    signal(SIGILL , cleanup);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &msl) < 0) 
    { 
        usage();
        return 0;
    }

    /* Check valid user and password */
    if (strlen(msl.user) < 4 || !msl.pwd) 
    {
        slog(0, "[WARN] Username and/or Password is not given\n");
        slog(0, "[INFO] Check usage with parameter -h\n");
        cli_init_msl(&msl);
    }

    /* Check info */
    //if (msl.info) get_info(&msl);

    /* Read sms info from user input */
    cli_init_sms(&msl);

    /* Send sms */
    slog(0, "[LIVE] Sending message...\n");

    ret = login_and_send(&msl);
    if (ret>=0) slog(0, "[LIVE] Message sent\n");
    else slog(0, "[ERROR] Can not send sms\n");

    return 0;
}