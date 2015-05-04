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
#include "slog.h"
#include "libmagtisun.h"


/*---------------------------------------------
| Initialise magtisun login variables
---------------------------------------------*/
void msl_init(MagtiSunLib* msl)
{
    bzero(msl->user, sizeof(msl->user));
    bzero(msl->num, sizeof(msl->num));
    bzero(msl->txt, sizeof(msl->txt));
    msl->pwd = NULL;
    msl->login = 0;
    msl->info = 0;
}


/*---------------------------------------------
| Read login information
---------------------------------------------*/
void msl_cli_init(MagtiSunLib* msl) 
{
    printf(ret_slog("[INPUT] Enter Username: "));
    scanf("%s", msl->user);
    msl->pwd = getpass(ret_slog("[INPUT] Enter Password: "));
}


/*---------------------------------------------
| Read sms information
---------------------------------------------*/
void msl_init_sms(MagtiSunLib* msl)
{
    printf(ret_slog("[INPUT] Enter Number: "));
    scanf("%s", msl->num);
    printf(ret_slog("[INPUT] Enter Text: "));
    scanf("%s", msl->txt);
}


/*---------------------------------------------
| Write function callback
---------------------------------------------*/
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    /* Write in file */
    return fwrite(ptr, size, nmemb, stream);
}


/*---------------------------------------------
| Check status in response
---------------------------------------------*/
int msl_check_status(char *fname) 
{
    /* Used variables */
    FILE* fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int ret = -1;

    /* Open templorary file */
    fp = fopen(fname, "r");
    if (fp != NULL) 
    {
        /* Get status */
        while ((read = getline(&line, &len, fp)) != -1) 
        {
            /* Find success str in response */
            if(strstr(line, "success") != NULL) 
            {
                ret = 1;
                break;
            }
        }
        fclose(fp);
    }

    return ret;
}


/*---------------------------------------------
| Get information about user
---------------------------------------------*/
int msl_get_info(MagtiSunLib* msl) 
{
    slog(0, "[TODO] Get infotmation is added to TODO list");
    exit(0);
}


/*---------------------------------------------
| Create templorary file for login session
---------------------------------------------*/
int msl_login(MagtiSunLib* msl) 
{
    slog(0, "[TODO] User login is added to TODO list");
    return 1;
}

/*---------------------------------------------
| Authorise and send sms
---------------------------------------------*/
int msl_send(MagtiSunLib* msl) 
{
    /* Used variables */
    FILE *fp;
    CURL *curl;
    CURLcode res;
    char login_url[128];
    char login_val[64];
    char sms_url[128];
    char sms_val[64];
    int done = 0;
    int ret = -1;

    /* Get ready for login */
    strcpy(login_url, "http://www.magtifun.ge/index.php?page=11&lang=ge");
    sprintf(login_val, "user=%s&password=%s", msl->user, msl->pwd);
    strcpy(sms_url, "http://www.magtifun.ge/scripts/sms_send.php");
    sprintf(sms_val, "recipients=%s&message_body=%s", msl->num, msl->txt);

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Check curl */
    while (curl && !done) 
    {
        /* Open output fileponter */
        fp = fopen(DISCARD_FILE, "w");
        if (fp == NULL) break;

        /* Get ready for login */
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_URL, &login_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &login_val);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(login_val));
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_LOGIN);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOCKIE_FILE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        /* Send post request to magtifun */
        res = curl_easy_perform(curl);
        fclose(fp);

        /* Check everything is ok */
        if(res != CURLE_OK) break;

        /* Open output fileponter */
        fp = fopen(SAVE_FILE, "w");
        if (fp == NULL) break;

        /* Get ready for send */
        curl_easy_setopt(curl, CURLOPT_URL, &sms_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &sms_val);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(sms_val));
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_SEND);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOCKIE_FILE);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        /* Send post request to magtifun */
        res = curl_easy_perform(curl);
        fclose(fp);

        /* Check everything is ok */
        if(res != CURLE_OK) break;
        ret = msl_check_status(SAVE_FILE);

        /* Exit from while */
        done = 1;
    }

    /* Cleanup curl */
    if (curl) curl_easy_cleanup(curl);
    curl_global_cleanup();

    /* Delete coockies */
    remove(COOCKIE_LOGIN);
    remove(COOCKIE_SEND);
    remove(SAVE_FILE);

    /* Return status */
    return ret;
}