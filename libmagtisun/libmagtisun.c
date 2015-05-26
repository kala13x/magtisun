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


/* C includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

/* Dependency includes */
#include <curl/curl.h>

/* Local includes */
#include "libmagtisun.h"


/* 
 * Get library version. Function returns version and build number of 
 * magtifun c library. Return value is static char pointer.
-*/
const char* msl_get_version()
{
    static char verstr[128];
    sprintf(verstr, "%s Build %d (%s)", MSLVERSION, MSLBUILD, __DATE__);
    return verstr;
}


/*
 * Safe exit if there is something wrong. Function handles illegal 
 * signals, cleans up everything and exits safe. So if there will 
 * be wrong user input, broken pipe or illegal signal, lib will be 
 * protected from exploitation.
 */
void msl_cleanup(int sig)
{
    /* Handle signals */
    if (sig == SIGILL || sig == SIGSEGV) 
        printf("MagtiSun: Incorrect inputed data\n");

    /* Make clean */
    remove(RESPONSE_FILE);
    remove(COOCKIE_LOGIN);
    remove(COOCKIE_SEND);
    exit(-1);
}


/*
 * Function decrypts recently crypted string with msl_crypt() and 
 * returns decrypted string. Return value char pointer. 
 *
 * Argument is char pointer of encrypted string.
 */
char* msl_decrypt(char *str) 
{
    /* Used variables */
    char* decrypted;
    unsigned int i;
    int key = 0xFACA;

    /* Decrypt */
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] + key;
    }
    decrypted = strdup(str);

    return decrypted;
}


/*
 * Encrypt string. Function takes string, encrypts it and returns
 * as char pointer. Its because of we dont want to make visible
 * our authorisation data for others.
 *
 * Argument is char pointer of that string which ecnryption we want.
 */
char* msl_crypt(char *str)
{
    /* Used variables */
    unsigned int i;
    int key = 0xFACA;
    char *crypted;

    /* Crypt */
    for(i=0;i<strlen(str);++i)
    {
        str[i] = str[i] - key;
    }
    crypted = strdup(str);

    return crypted;
}


/*
 * Initialize magtisun library. Function takes empty pointer of 
 * MagtiSunLib structure and initializes it for future use. It
 * also checks if user is alredy logged in and writes info in login flag.
 *
 * If user is logged in, msl->logged flag will be 1, otherwise it will be 0.
 */
void msl_init(MagtiSunLib* msl)
{
    /* Used variables */
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char* tmp;

    /* Catch ilegal signal */
    signal(SIGINT, msl_cleanup);
    signal(SIGSEGV, msl_cleanup);
    signal(SIGILL , msl_cleanup);

    /* Clear values */
    bzero(msl->usr, sizeof(msl->usr));
    bzero(msl->pwd, sizeof(msl->pwd));
    bzero(msl->num, sizeof(msl->num));
    bzero(msl->txt, sizeof(msl->txt));
    bzero(msl->name, sizeof(msl->name));

    /* Set flags */
    msl->logged = 0;
    msl->mleft = -1;

    /* Open session file */
    fp = fopen(LOGIN_FILE, "r");
    if (fp != NULL) 
    {
        /* Get status */
        while ((read = getline(&line, &len, fp)) != -1) 
        {
            /* Decrypt line */
            line = msl_decrypt(line);

            /* Find user in line */
            if(strstr(line, "user") != NULL) 
            {
                /* Get user info */
                tmp = strtok(line, ":");
                if (tmp) strcpy(msl->usr, tmp);
                tmp = strtok(NULL, ":");
                if (tmp) strcpy(msl->pwd, tmp);

                /* Check valid usr/pwd */
                if (strlen(msl->usr) > 4 && strlen(msl->pwd) > 4) 
                    msl->logged = 1;
            }
        }
        fclose(fp);
    }
}


/*
 * Initialise login variables from commandline input. Function initializes
 * username and password (invisible password input) from commandline and
 * saves values at:
 * 
 * @ msl->usr - username
 * @ msl->pwd - password
 *
 * Argument is pointer of MagtiSunLib structure
 */
void msl_cli_init(MagtiSunLib* msl) 
{
    /* Get username */
    printf("MagtiSun: Enter Username: ");
    scanf("%s", msl->usr);

    /* Get password (invisible) */
    char* pwd = getpass("MagtiSun: Enter Password: ");
    strcpy(msl->pwd, pwd);
}


/*
 * Initialize sms variables from commandline input. Function initializes
 * mobile number and sms text from commandline and saves values at:
 * 
 * @ msl->num - adress number
 * @ msl->txt - sms text
 *
 * Argument is pointer of MagtiSunLib structure
 */
void msl_init_sms(MagtiSunLib* msl)
{
    /* Get number */
    printf("MagtiSun: Enter Number: ");
    scanf("%s", msl->num);

    /* Get sms text */
    printf("MagtiSun: Enter Text: ");
    scanf("%s", msl->txt);
}


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    /* Write in file */
    return fwrite(ptr, size, nmemb, stream);
}


/* Check status in response */
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


/* Check get info response */
int msl_check_info(char* fname, MagtiSunLib* msl) 
{
    /* Used variables */
    FILE* fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char* name;
    int ret = -1;

    /* Open templorary file */
    fp = fopen(fname, "r");
    if (fp != NULL) 
    {    
        while ((read = getline(&line, &len, fp)) != -1) 
        {
            /* Find left messages in response */
            if(strstr(line,"xxlarge dark english")!=NULL)
            msl->mleft = atoi(line+100);

            /* Find name in response */
            if(strstr(line,"center_text dark english")!=NULL)
            {
                name = strdup(line+82);
                sscanf(name, "%32[^<]<", msl->name);
            }
        }

        /* Close file */
        fclose(fp);
    }

    /* Check valid data */
    if(strlen(msl->name) > 4 && msl->mleft >= 0)
        ret = 1;

    return ret;
}


/*
 * Get user information from magtifun. Function parses user and number of 
 * left messages at magtifun and saves values at (login variables must be initialized):
 *
 * @ msl->name - username at magtifun
 * @ msl->mleft - left messages at magtifun
 *
 * Argument is pointer of MagtiSunLib structure
 */
int msl_get_info(MagtiSunLib* msl) 
{
    /* Used variables */
    FILE *fp;
    CURL *curl;
    CURLcode res;
    char val[512];
    char url[128];
    int ret = -1;

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Check curl */
    if (curl) 
    {
        /* Open output fileponter */
        fp = fopen(RESPONSE_FILE, "w");
        if (fp != NULL) 
        {
            /* Get ready for login */
            strcpy(url, "http://www.magtifun.ge/index.php?page=11&lang=ge");
            sprintf(val, "user=%s&password=%s", msl->usr, msl->pwd);

            /* Set curl options for login */
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_URL, &url);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &val);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(val));
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

            /* Open response fileponter */
            if (res == CURLE_OK) 
                ret = msl_check_info(RESPONSE_FILE, msl);
        }

        /* Cleanup */
        curl_easy_cleanup(curl);
        remove(RESPONSE_FILE);
        remove(COOCKIE_LOGIN);
        remove(COOCKIE_FILE);
    }

    /* Global cleanup curl */
    curl_global_cleanup();

    return ret;
}


/*
 * Offline log out. Function deletes templorary file where is written 
 * encrypted username and password with msl_login() function.
 */
void msl_logout() 
{
    remove(LOGIN_FILE);
    exit(1);
}


/*
 * Offline login. Function encrypts username and password and saves it in
 * /tmp/msl file. If you will cat that file, you will not be able to see user
 * and password which written in that file. After successful login, there is not
 * required initialization of login variables. Username and password will be
 * initialized from file with the msl_init() function.
 *
 * Argument is pointer of MagtiSunLib structure
 */
int msl_login(MagtiSunLib* msl) 
{
    /* Session info */
    char session[64];
    char* crypted;

    /* Remove existing fole */
    remove(LOGIN_FILE);

    /* Open file pointer */
    FILE *fp = fopen(LOGIN_FILE, "a");
    if (fp != NULL) 
    {
        /* Crypt session key */
        sprintf(session, "%s:%s:user", msl->usr, msl->pwd);
        crypted = msl_crypt(session);

        /* Write key in file */
        fprintf(fp, "%s", crypted);
        msl->logged = 1;
        
        /* Close file and return */
        fclose(fp);
        return 1;
    }

    return 0;
}


/*
 * Send message. After initialization of login and sms variables,
 * function sends sms to the destination number. Here is variables which
 * must be initialized to use this function correctly:
 *
 * @ msl->usr - username of magtifun
 * @ msl->pwd - password of magtifun
 * @ msl->num - adress number
 * @ msl->txt - text of message
 */
int msl_send(MagtiSunLib* msl) 
{
    /* Used variables */
    FILE *fp;
    CURL *curl;
    CURLcode res;
    char val[512];
    char url[128];
    int ret = -1;

    /* Initialise curl */
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    /* Check curl */
    if (curl) 
    {
        /* Open output fileponter */
        fp = fopen(DISCARD_FILE, "w");
        if (fp != NULL) 
        {
            /* Get ready for login */
            strcpy(url, "http://www.magtifun.ge/index.php?page=11&lang=ge");
            sprintf(val, "user=%s&password=%s", msl->usr, msl->pwd);

            /* Set curl options for login */
            curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_easy_setopt(curl, CURLOPT_URL, &url);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &val);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(val));
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

            /* Open response fileponter */
            if (res == CURLE_OK) fp = fopen(RESPONSE_FILE, "w");
            if (fp != NULL) 
            {
                /* Get ready for send */
                strcpy(url, "http://www.magtifun.ge/scripts/sms_send.php");
                sprintf(val, "recipients=%s&message_body=%s", msl->num, msl->txt);

                /* Set curl options for send */
                curl_easy_setopt(curl, CURLOPT_URL, &url);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &val);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(val));
                curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1);
                curl_easy_setopt(curl, CURLOPT_COOKIEJAR, COOCKIE_SEND);
                curl_easy_setopt(curl, CURLOPT_COOKIEFILE, COOCKIE_FILE);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

                /* Send post request to magtifun */
                res = curl_easy_perform(curl);
                fclose(fp);

                /* Check everything is ok */
                if(res == CURLE_OK) 
                    ret = msl_check_status(RESPONSE_FILE);
            }
        }

        /* Cleanup */
        curl_easy_cleanup(curl);
        remove(RESPONSE_FILE);
        remove(COOCKIE_LOGIN);
        remove(COOCKIE_SEND);
    }

    /* Global cleanup curl */
    curl_global_cleanup();

    return ret;
}