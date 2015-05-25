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


/* For include header in CPP code */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Coockie files */
#define RESPONSE_FILE "/tmp/mslres.log"
#define COOCKIE_LOGIN "cookie-name"
#define COOCKIE_SEND "cookie-name-send"
#define COOCKIE_FILE "cookie"
#define DISCARD_FILE "/dev/null"
#define LOGIN_FILE "/tmp/msl"

/* Version and build number */
#define MSLVERSION "1.0.2 Snapshot"
#define MSLBUILD 25


/* Structure of user variables */
typedef struct {
    char name[128];
    char txt[512];
    char pwd[32];
    char num[16];
    char usr[16];
    short logged;
    int mleft;
} MagtiSunLib;


/* 
 * Get library version. Function returns version and build number of 
 * magtifun c library. Return value is static char pointer.
-*/
const char* msl_get_version();


/*
 * Function decrypts recently cripted string with msl_crypt() and 
 * returns decrypted string. Return value char pointer. 
 *
 * @ Argument is char pointer where encrypted string is written.
 */
char* msl_decrypt(char *str);


/*
 * Encrypt string. Function takes string, encrypts it and returns
 * as char pointer. Its because of we dont want to make visible
 * our authorisation data for others.
 *
 * @ Argument is char pointer where is witten string to encrypt.
 */
char* msl_crypt(char *str);


/*
 * Initialize magtisun library. Function takes empty pointer of 
 * MagtiSunLib structure and initializes it for future use. It
 * also checks if user is alredy logged in and writes info in login flag.
 *
 * If user is logged in, msl->logged flag vill be 1, otherwise it will be 0.
 */
void msl_init(MagtiSunLib* msl);


/*
 * Initialise login variables from commandline input. Function initializes
 * username and password (invisible password input) from commandline and
 * saves values at:
 * 
 * @ msl->usr - username
 * @ msl->pwd - password
 *
 * @ Argument is pointer of MagtiSunLib structure
 */
void msl_cli_init(MagtiSunLib* msl);


/*
 * Initialize sms variables from commandline input. Function initializes
 * mobile number and sms text from commandline and saves values at:
 * 
 * @ msl->num - adress number
 * @ msl->txt - sms text
 *
 * @ Argument is pointer of MagtiSunLib structure
 */
void msl_init_sms(MagtiSunLib* msl);


/*
 * Get user information from magtifun. Function parses user and number of 
 * left messages at magtifun and saves values at (login variables must be initialized):
 *
 * @ msl->name - username at magtifun
 * @ msl->mleft - left messages at magtifun
 *
 * @ Argument is pointer of MagtiSunLib structure
 */
int msl_get_info(MagtiSunLib* msl);


/*
 * Offline login. Function encrypts username and password and saves it in
 * /tmp/msl file. If you will cat that file, you will not be able to see user
 * and password which written in that file. After successful login, there is not
 * required initialization of login variables. Username and password will be
 * initialized from file with the msl_init() function.
 *
 * @ Argument is pointer of MagtiSunLib structure
 */
int msl_login(MagtiSunLib* msl);


/*
 * Offline log out. Function deletes templorary file where is written 
 * encrypted username and password with msl_login() function.
 */
void msl_logout();


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
int msl_send(MagtiSunLib* msl);


/* For include header in CPP code */
#ifdef __cplusplus
}
#endif
