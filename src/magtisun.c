/*
 * MagtiSun is commandline application which makes you able to send sms 
 * with terminal via magtifun. Also you can implement libmagtisun in 
 * another C/C++ application prjects to send sms from your application 
 * with or without graphical interface.
 *
 *  Copyright (c) 2015 Sun Dro (a.k.a. 7th Ghost)
 *  Web: http://off-sec.com/ ; E-Mail: kala0x13@gmail.com
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include "../lib/magtisun.h"
#include "../slog/slog.h"
#include "stdinc.h"
#include "info.h"


/* MagtiSun Flags*/
typedef struct {
    short info;
    short login;
    short logout;
} MagtiSunFlags;


void init_flags(MagtiSunFlags* msf) 
{
    msf->info = 0;
    msf->login = 0;
    msf->logout = 0;
}


void init_info(MagtiSunLib* msl) 
{
    /* Get username */
    printf("%s", ret_slog("[INPUT] Enter Username: "));
    scanf("%s", msl->usr);

    /* Get password (hidden input) */
    char* pwd = getpass(ret_slog("[INPUT] Enter Password: "));
    strcpy(msl->pwd, pwd);
}


void init_sms(MagtiSunLib* msl)
{
    /* Get number */
    printf("%s", ret_slog("[INPUT] Enter Number: "));
    scanf("%s", msl->num);

    /* Get sms text */
    printf("%s", ret_slog("[INPUT] Enter Text: "));
    scanf("%s", msl->txt);
}


void err_exit(char *message) 
{
    slog(0, SLOG_ERROR, "%s", message);
    slog(0, SLOG_INFO, "The reason can be wrong username and/or password");
    slog(0, SLOG_INFO, "Also make sure magtifun.ge is not down");
}


/* Parse cli arguments */
static int parse_arguments(int argc, char *argv[], MagtiSunFlags* msf)
{
    int c;
    while ( (c = getopt(argc, argv, "l1:o1:i1:h1")) != -1) {
        switch (c) {
        case 'l':
            msf->login = 1;
            break;
        case 'o':
            msf->logout = 1;
            break;
        case 'i':
            msf->info = 1;
            break;
        case 'h':
        default:
            return -1;
        }
    }

    return 0;
}


int main(int argc, char **argv)
{
    /* Used variables */
    MagtiSunFlags msf;
    MagtiSunLib msl;
    char answer[8];

    /* Greet users */
    greet();

    /* Initialise everything */
    init_flags(&msf);
    msl_init(&msl);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &msf) < 0) { usage(); return 0; }
    if (msf.logout) { slog(0, SLOG_LIVE, "Logging out"); msl_logout(); }
    if (msl.logged) slog(0, SLOG_INFO, "Logged in as: %s", msl.usr);

    /* Login user */
    if (msf.login)
    {
        /* Check logged user */
        if (msl.logged) 
        { 
            slog(0, SLOG_LIVE, "Please log out first"); 
            exit(0); 
        }

        /* User input info */
        init_info(&msl);

        if(msl_login(&msl)) 
            slog(0, SLOG_INFO, "Logged in as: %s", msl.usr);

        exit(0);
    }

    /* Check valid username and password */
    if (strlen(msl.usr) < 4 || strlen(msl.pwd) < 4) 
    {
        slog(0, SLOG_INFO, "Not logged in");
        init_info(&msl);
    }

    /* Check info */
    if (msf.info) 
    {
        /* Get info */
        if(msl_get_info(&msl) >= 0) 
        {
            slog(0, SLOG_LIVE, "User: %s", msl.name);
            slog(0, SLOG_LIVE, "Messages left: %d", msl.mleft);
            exit(0);
        }
        else err_exit("Can not get info");
    }

    /* Read sms info from user input */
    init_sms(&msl);

    /* Send sms */
    slog(0, SLOG_LIVE, "Sending message...");
    if (msl_send(&msl) >= 0) 
    {
        slog(0, SLOG_LIVE, "Message sent");

        /* Stay logged */
        if (!msl.logged) 
        {
            /* User input answer */
            printf("%s", ret_slog("[LIVE]  Do you want to stay logged? (y/n): "));
            scanf("%s", answer);

            /* Check answer answer */
            if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0)
                if(msl_login(&msl)) slog(0, SLOG_LIVE, "Saved logged session");
        }
    }
    else err_exit("Can not send sms");

    return 0;
}