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
static int parse_arguments(int argc, char *argv[], MagtiSun_Login* msl)
{
    int c;
    while ( (c = getopt(argc, argv, "u:p:h1")) != -1) {
        switch (c) {
        case 'u':
            msl->user = strdup(optarg);
            break;
        case 'p':
            msl->pwd = strdup(optarg);
            break;
        case 'h':
        default:
            usage();
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
    int ret;

    /* Initialise variables */
    init_slog("magtisun", 3);
    init_msl(&msl);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &msl)) return 0;

    /* Check valid user and password */
    if (!msl.user || !msl.pwd) 
    {
        usage();
        slog(0, "[ERROR] Username and/or Password is not given");
        return 1;
    }

    /* Print user information */
    slog(0, "Username: %s", msl.user);
    slog(0, "Password: %s", msl.pwd);

    /* Login to magtifun */
    ret = make_login(msl.user, msl.pwd);
    if (ret>=0) slog(0, "[LIVE] Successfuly authorised");

    return 0;
}