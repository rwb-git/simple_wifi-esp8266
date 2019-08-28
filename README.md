These files work in platformio, and also work as-is in the Arduino IDE as follows:

Make a directory with a name like simple_wifi or whatever you like, and copy all the cpp and h files (skip platformio.ini) files into that directory, and change the name of main.cpp to simple_wifi.ino or the name you chose. All the other cpp and header files compile as-is.

This code works with my Android app "simple_wifi-android". You will need the IP that your router assigns to your esp device. I like to assign a fixed IP like 10.0.0.205 to my device, since scanning over a range that includes computers and phones sometimes hangs, so I put an IP with a high number like 205 and then scan from 195 to 208 for example.

You need to enter your router's ssid and password in simple_wifi.ino, and you might need to go into your router configuration and allow the esp8266.
