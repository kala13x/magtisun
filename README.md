MagtiSun - Version: 0.0.4 Beta BUILD 13
----

MagtiSun is commandline application which makes you able to send sms with terminal via magtifun sms API. Also you can implement libmagtisun in another C/C++ CLI application prjects to send sms from your application without graphical interface. Software is written for educational purposes and is distributed in the hope that it will be useful for anyone interested in this field.

###Usage
```
magtisun [-u <username>] [-l] [-o] [-i] [-h]
options are:
 -u <username>       # magtifun user name
 -l                  # do login
 -o                  # logout from app
 -i                  # get and print user information
 -h                  # prints version and usage
```
Software has invisible password input for security reasons.

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

###Get more info from blog
- Offencive-Security Georgia [http://off-sec.com/](http://off-sec.com)
