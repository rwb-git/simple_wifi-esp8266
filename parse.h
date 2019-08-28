// this file is the same in simple_wifi and wifi_AP

#include <ESP8266WiFi.h>            // this includes wificlient, wifiserver, and several other header files

//#define serial1 1         // un-comment this to enable lots of printing to the serial monitor. sidenote: when I flash my esp and have the USB cable
                            // connected, my esp will eventually hang. I think it's stuck in the mode where it is waiting for the bootloader to write
                            // the flash. sometimes the watchdog timers reset and sometimes they don't. but when the USB cable is disconnected, my
                            // device runs for many hours without resetting or hanging. So, if your esp gets stuck and stops cycling the leds, try
                            // disconnecting the USB cable, which means the esp will need external power.


extern WiFiClient client; 

extern uint32_t heap;

extern uint32_t uptime_minutes;

extern WiFiServer server;

extern uint16_t app_msg;

void parse_app_msg(String pay);

void lf(void);


