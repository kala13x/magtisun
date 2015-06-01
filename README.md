MagtiSun - Version: 1.0 build 31
----

 MagtiSun is commandline application which makes you able to send sms with terminal via magtifun. Also you can implement libmagtisun in another C/C++ application prjects to send sms from your application with or without graphical interface. Software is written for educational purposes and is distributed in the hope that it will be useful for anyone interested in this field.

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
If you dont want to type your username and password everytime when you launch magtisun, you can just login -l and magtisun will crypt and save your user information in templorary file at your /tmp/ directory. Because of known security reasons, that password must not be visible for others, magtisun crypts key before it saves in file. If you will cat that file, you will not be able to see password. String in file will be something like that:
```
����������������
```
When you launch application after login, magtisun will decrypt this file to get user and password for authorisation at magtiofun. If you done everything and you dont need logged session, you can just logout from application with command:
```
magtisun -o
```
This command will remove templorary file where your encrypted key is saved.

###Get user information
You can get information from magtifun such as your name at magtifun and number of how many sms do you left.

The command is simple:
```
magtisun -i
```

Output example:

```
[kala@build-box magtisun]$ ./magtisun -i
====================================================
MagtiSun-SMS: 0.1.2 Snapshot Build 23 (May  6 2015)
====================================================
2015.05.06-12:34:40 - [LIVE] Logged in as: 598998592
2015.05.06-12:34:40 - [LIVE] User: Travis Jenkins
2015.05.06-12:34:40 - [LIVE] Messages left: 47
```

###Compilation
Compilation of this project is possible with Makefile (just type 'make' in terminal).
If you want to compile project manualy, at first you mast compile libmagtifun and slog. 

```
git clone git@github.com:kala13x/magtisun.git
cd magtisun/libmagtisun
make
cd ../slog
make
cd ..
make
sudo make install
```

Otherwise you can just build whole project with 'build.sh' script

```
git clone git@github.com:kala13x/magtisun.git
cd magtisun
chmod +x build.sh
./build.sh
```

###Dependencies
Make sure you have [curl development library](https://github.com/bagder/curl) installed on your computer to compile magtisun.

###Standalone Library and API Usage
#####LibMagtiSun - Version: 1.0.2 Snapshot BUILD 31
You can implement this library in another C/C++ project. You can copy files from libmagtisun directory and compile it by yourself.
```
cd libmagtisun
make
```
Just include header file in your application and you will be able to use those functions which are defined in header file. Also please make sure that you are linking libmagtisun.a shared library while compiling your project.

You can see examples in Makefile and magtisun.c files to see how to compile correctly and use functions from libmagtisun. 

You can see API documentation in libmagtisun.h file. Each function has detailed documentations.


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
