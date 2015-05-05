MagtiSun - Version: 0.0.6 Beta BUILD 16
----

MagtiSun is commandline application which makes you able to send sms with terminal via magtifun sms API. Also you can implement libmagtisun in another C/C++ CLI application prjects to send sms from your application without graphical interface. Software is written for educational purposes and is distributed in the hope that it will be useful for anyone interested in this field.

###Usage
```
magtisun [-l] [-o] [-i] [-h]
options are:
 -l                  # do login
 -o                  # logout from app
 -i                  # get and print user information
 -h                  # prints version and usage
```
Software has invisible password input for security reasons.

###Login
If you dont want to type your username and password everytime when you launch magtisun, you can just login in application and magtisun will crypt and save your user information in templorary file in your /tmp/ directory. Because of known security reasons, that password must not be seen to others, magtisun crypts key before it saves it to file. If you do cat of that file, you will not be able to see password. File will be something like that:
```
����������������
```
Wen you launch application afther login, magtisun will decrypt this file to get user and password for authorisation on magtiofun. If you done everything and you dont need logined session, you can just logout from application with command:
```
magtisun -o
```
This command will remove templorary file where is saved your encrypted key.


###Compilation
Compilation of this project is possible with Makefile (just type 'make' in terminal).
```
git clone git@github.com:kala13x/magtisun.git
cd  magtisun
make
sudo make install
```

###Dependencies
Make sure you have [curl development library](https://github.com/bagder/curl) installed on your computer to compile magtisun.

###API Usage
If you want to implement this library in another C/C++ project, you need only two files:
```
libmagtisun.c
libmagtisun.h
```
Just include header file in your application and you will be able to use those functions which are defined in header file. Also please make sure that you are compiling and linking libmagtisun.c while compiling your project.

You can see examples in Makefile and magtisun.c files to see how to compile correctly and use functions from libmagtisun. 

Full API documentation will be available soon.

###Todo
- get and print user information

###Simple CLI interface
Here is an example output of MagtiSun usage:
```
[kala@build-box magtisun]$ ./magtisun 
====================================================
MagtiSun-SMS: 0.0.4 Beta Build 13 (May  5 2015)
====================================================
2015.05.05-00:50:38 - [LIVE] Not logged in
2015.05.05-00:50:38 - [INPUT] Enter Username: kala13x
2015.05.05-00:50:48 - [INPUT] Enter Password: 
2015.05.05-00:50:51 - [INPUT] Enter Number: 598998592
2015.05.05-00:50:56 - [INPUT] Enter Text: dzudzu
2015.05.05-00:50:59 - [LIVE] Sending message...
2015.05.05-00:51:11 - [LIVE] Message sent
```

###Feel free to fork
You can fork, modify and change the code unther the GNU GPL 3 license. The project contains LICENSE file to see full license description.

###Get more info from blog
- Offencive-Security Georgia [http://off-sec.com/](http://off-sec.com)
