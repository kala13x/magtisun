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
}


/*---------------------------------------------
| Write callback to save coockies in file
---------------------------------------------*/
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
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

    /* Get ready for login */
    strcpy(login_url, "http://www.magtifun.ge/index.php?page=11&lang=ge");
    sprintf(post_val, "user=%s&password=%s", user, pwd);

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Remove existing coockie file */
    remove(COOCKIE_LOGIN);

    /* Check curl */
    if (curl) 
    {
        /* Get ready */
        curl_easy_setopt(curl, CURLOPT_URL, login_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_val);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post_val));
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_LOGIN);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.tmp");

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