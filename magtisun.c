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


#include "lib/libmagtisun.h"
#include "stdinc.h"
#include "slog.h"
#include "info.h"


/*---------------------------------------------
| Structure of flags
---------------------------------------------*/
typedef struct {
    short info;
    short login;
    short logout;
} MagtiSunFlags;


/*---------------------------------------------
| Initialise flags
---------------------------------------------*/
void init_flags (MagtiSunFlags* msf) 
{
    msf->info = 0;
    msf->login = 0;
    msf->logout = 0;
}


/*---------------------------------------------
| Read login information
---------------------------------------------*/
void user_init_info(MagtiSunLib* msl) 
{
    /* String variable */
    char *str;

    /* Get username */
    str = ret_slog("[INPUT] Enter Username: ");
    printf("%s", str);
    scanf("%s", msl->usr);

    /* Get password (invisible) */
    str = ret_slog("[INPUT] Enter Password: ");
    char* pwd = getpass(str);
    strcpy(msl->pwd, pwd);
}


/*---------------------------------------------
| Read sms information
---------------------------------------------*/
void user_init_sms(MagtiSunLib* msl)
{
    /* String variable */
    char *str;

    /* Get number */
    str = ret_slog("[INPUT] Enter Number: ");
    printf("%s", str);
    scanf("%s", msl->num);

    /* Get sms text */
    str = ret_slog("[INPUT] Enter Text: ");
    printf("%s", str);
    scanf("%s", msl->txt);
}


/*---------------------------------------------
| Parse cli arguments
---------------------------------------------*/
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


/*---------------------------------------------
| Main function
---------------------------------------------*/
int main(int argc, char **argv)
{
    /* Used variables */
    MagtiSunFlags msf;
    MagtiSunLib msl;
    char answer[8];
    char* str;

    /* Greet users */
    greet();

    /* Initialise variables */
    init_slog("magtisun", 3);
    init_flags(&msf);
    msl_init(&msl);

    /* Parse Commandline Arguments */
    if (parse_arguments(argc, argv, &msf) < 0) 
    { 
        usage();
        return 0;
    }

    /* Check logout argument */
    if (msf.logout) 
    {
        slog(0, "[LIVE] Logging out");
        msl_logout();
    }

    /* Check logged user */
    if (msl.logged) 
        slog(0, "[LIVE] Logged in as: %s", msl.usr);

    /* Login user */
    if (msf.login)
    {
        /* Check logged user */
        if (msl.logged) 
        {
            slog(0, "[LIVE] Please log out first");
            exit(0);
        }

        /* User input info */
        user_init_info(&msl);

        /* Do login */
        if(msl_login(&msl)) 
            slog(0, "[LIVE] Logged in as: %s", msl.usr);
        exit(0);
    }

    /* Check valid username and password */
    if (strlen(msl.usr) < 4 || strlen(msl.pwd) < 4) 
    {
        slog(0, "[LIVE] Not logged in");
        user_init_info(&msl);
    }

    /* Check info */
    if (msf.info) 
    {
        /* Get info */
        if(msl_get_info(&msl) >= 0) 
        {
            slog(0, "[LIVE] User: %s", msl.name);
            slog(0, "[LIVE] Messages left: %d", msl.mleft);
            exit(0);
        }
        else 
        {
            slog(0, "[ERROR] Can not get info");
            slog(0, "[INFO] The reason can be wrong username and/or password");
            slog(0, "[INFO] Also make sure magtifun.ge is not down");
            exit(0);
        }
    }

    /* Read sms info from user input */
    user_init_sms(&msl);

    /* Send sms */
    slog(0, "[LIVE] Sending message...");
    if (msl_send(&msl) >= 0) 
    {
        slog(0, "[LIVE] Message sent");

        /* Stay logged */
        if (!msl.logged) 
        {
            /* User input answer */
            str = ret_slog("[LIVE] Do you want to stay logged? (y/n): ");
            printf("%s", str);
            scanf("%s", answer);

            /* Check answer answer */
            if (strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0) 
            {
                if(msl_login(&msl))
                    slog(0, "[LIVE] Saved logged session");
            }
        }
    }
    else 
    {
        slog(0, "[ERROR] Can not send sms");
        slog(0, "[INFO] The reason can be wrong username and/or password");
        slog(0, "[INFO] Also make sure magtifun.ge is not down");
    }

    return 0;
}