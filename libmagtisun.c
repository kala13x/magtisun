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
#include "libmagtisun.h"


/*---------------------------------------------
| Initialise magtisun login variables
---------------------------------------------*/
void init_msl(MagtiSun_Login* msl)
{
    msl->user = NULL;
    msl->pwd = NULL;
    bzero(msl->num, sizeof(msl->num));
    bzero(msl->txt, sizeof(msl->txt));
}


/*---------------------------------------------
| Get authorisation at magtifun
---------------------------------------------*/
int make_login(char *user, char* pwd) 
{
    /* Used variables */
    CURL *curl;
    CURLcode res;
    char login_url[128];
    char post_val[64];
    int ret = 0;

    /* Remove existing coockie file */
    remove(COOCKIE_LOGIN);

    /* Get ready for login */
    strcpy(login_url, "http://www.magtifun.ge/index.php?page=11&lang=ge");
    sprintf(post_val, "user=%s&password=%s", user, pwd);

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Check curl */
    if (curl) 
    {
        /* Get ready */
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_URL, &login_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &post_val);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post_val));
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_LOGIN);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOCKIE_FILE);

        /* Send post request to magtifun */
        res = curl_easy_perform(curl);

        /* Check everything is ok */
        if(res != CURLE_OK) ret = -1;

        /* Cleanup */
        curl_easy_cleanup(curl);
    }

    /* Return with status */
    return ret;
}


/*---------------------------------------------
| Send sms with magtifun
---------------------------------------------*/
int send_sms(char *num, char* txt) 
{
    /* Used variables */
    CURL *curl;
    CURLcode res;
    char sms_url[128];
    char post_val[64];
    int ret = 0;

    /* Remove existing coockie file */
    remove(COOCKIE_SEND);

    /* Get ready for login */
    strcpy(sms_url, "http://www.magtifun.ge/scripts/sms_send.php");
    sprintf(post_val, "recipients=%s&message_body=%s", num, txt);

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Check curl */
    if (curl) 
    {
        /* Get ready */
        curl_easy_setopt(curl, CURLOPT_URL, &sms_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &post_val);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post_val));
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_SEND);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOCKIE_FILE);

        /* Send post request to magtifun */
        res = curl_easy_perform(curl);

        /* Check everything is ok */
        if(res != CURLE_OK) ret = -1;

        /* Cleanup */
        curl_easy_cleanup(curl);
    }

    /* Return with status */
    return ret;
}


/*---------------------------------------------
| Authorise and send sms
---------------------------------------------*/
int login_and_send(MagtiSun_Login* msl) 
{
    /* Used variables */
    CURL *curl;
    CURLcode res;
    char login_url[128];
    char login_val[64];
    char sms_url[128];
    char sms_val[64];
    int ret = 0;

    /* Remove existing coockie file */
    remove(COOCKIE_LOGIN);
    remove(COOCKIE_SEND);

    /* Get ready for login */
    strcpy(login_url, "http://www.magtifun.ge/index.php?page=11&lang=ge");
    sprintf(login_val, "user=%s&password=%s", msl->user, msl->pwd);
    strcpy(sms_url, "http://www.magtifun.ge/scripts/sms_send.php");
    sprintf(sms_val, "recipients=%s&message_body=%s", msl->num, msl->txt);

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Check curl */
    if (curl) 
    {
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

        /* Send post request to magtifun */
        res = curl_easy_perform(curl);

        /* Check everything is ok */
        if(res != CURLE_OK) ret = -1;

        /* Get ready send */
        curl_easy_setopt(curl, CURLOPT_URL, &sms_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &sms_val);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(sms_val));
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_SEND);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOCKIE_FILE);

        /* Send post request to magtifun */
        res = curl_easy_perform(curl);

        /* Check everything is ok */
        if(res != CURLE_OK) ret = -1;

        /* Cleanup */
        curl_easy_cleanup(curl);
    }

    /* Return with status */
    return ret;
}