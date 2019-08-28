// *    this works with simple_wifi android app, as does sketch wifi_AP

#include "parse.h"
#include "server_loop.h"

// enter your router SSID and password
const char * ssid = "NETGEAR84";
const char * password = "rb76543aaa789&*()cvbn";

#define one_sec_led LED_BUILTIN  //D4    // builtin led on nodemcu

uint32_t rgbcycles;



//-----------------------------------------------------------------------------------------------------


void setup() {

  ESP.wdtEnable(2000); // soft wdt works without this
  
  pinMode(one_sec_led, OUTPUT);

  heap = ESP.getFreeHeap();  
  
  #ifdef serial1

  Serial.begin(115200);

  Serial.println();

  Serial.printf("Connecting to %s ", ssid);

  Serial.print(" heap ");
  Serial.println(heap);

  #endif


  WiFi.persistent(false); // according to readthedocs, the flash can wear out if I call WiFi.begin(ssid,pwd) too many times. setting persistent = false is supposed to make it use whatever is already there and not re-write it. so, I think
                          // that I can leave this alone in every sketch as long as I'm using the same router ssid and pwd. 
  
  WiFi.mode(WIFI_STA);

//  WiFi.begin(); // this will use whatever is in flash and will not write it

  WiFi.begin(ssid, password);   // I have to enable this if I use a new device that does not have my router ssid/pwd already stored in flash.
  
  while (WiFi.status() != WL_CONNECTED){
    
    delay(500);
    
    #ifdef serial1    
    Serial.print(".");
    #endif    
  }
  

  #ifdef serial1  
  Serial.println(" connected");
  #endif

  server.begin();

  #ifdef serial1
  Serial.print("\n");
  Serial.print(WiFi.localIP());
  #endif
}


//-----------------------------------------------------------------------------


uint32_t ccnt;

uint16_t ledcnt;


void loop() {

  ccnt = ESP.getCycleCount();   // 2^32 / 80e6 = 53.7 seconds to rollover, esp clock is 80 mhz, so there are 80e6 cycles per second, and the count 
                                //is stored in 32 bits. 

  uptime_minutes = millis() / 60000;  // this tells the app how long the esp has been running without a reset or power cycle.
                                      // millis() rolls over every 49.7 days i think: 2^32 / 1000 / 60 / 60 / 24 = 49.7 days to rollover

  server_loop();    // check for clients connecting

  if ((ccnt - rgbcycles) > 250000){  // this flashes the built-in led about once per second. one half second is about 0.5 / 160 / 80e6 = 250000

    // when getCycleCount rolls over, ccnt - rgbcycles will be negative, but I think the unsigned math results in a large unsigned value 
    // which enables this loop to handle the rollover with an error less than 3.2 msec
    
      ledcnt++;
  
      if (ledcnt == 160){
  
        digitalWrite(one_sec_led,LOW);
        
      } else if (ledcnt == 320){
  
        ledcnt = 0;
  
        digitalWrite(one_sec_led,HIGH);
      }
  
    rgbcycles = ccnt;
  }
}
