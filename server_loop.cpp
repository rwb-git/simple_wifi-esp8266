// this file is identical in wifi_AP and simple_wifi

#include "server_loop.h"
#include "parse.h"




void ack_scan(){

    char buf[300];

    // needs final " " or app says not an integer (if final entity is a number)
    
    sprintf(buf,"%d %d %d \r\n",app_msg,44,55); 

    client.print(buf);
  
}


void change_spaces_to_underscores(char * cc){
  
   char * loc;
  
   while (strchr(cc,' ')){  // replace blanks with underscores because app splits tokens on spaces

      loc = strchr(cc,' ');

      *loc = '_';
   }
}


void send_status(){

    char buf[300];

    String resetreason = ESP.getResetReason();

    char * cc = &resetreason[0];

    change_spaces_to_underscores(cc);
  
    String sdk_str = ESP.getSdkVersion();

    cc = &sdk_str[0];
    
    change_spaces_to_underscores(cc);
    
    heap = ESP.getFreeHeap();  

   // String core = ESP.getCoreVersion();
   // String full = ESP.getFullVersion();
  
   // uint8_t bootver = ESP.getBootVersion();
   // uint8_t bootmode = ESP.getBootMode();
  
    uint8_t cpu = ESP.getCpuFreqMHz();
  
    uint32_t sketchspace = ESP.getFreeSketchSpace();
    
    String resetinfo = ESP.getResetInfo();

    // needs final " " or app says not an integer (if final entity is a number)
    
    sprintf(buf,"%d %d %d %s %s %d %d \r\n",app_msg,heap,uptime_minutes,resetreason.c_str(),sdk_str.c_str(),cpu,sketchspace); 

    client.print(buf);
  
}



void server_loop(){
  
  client = server.available();    // wait for a client to connect. this could be a web browser, android app, etc.
  
  if (client){

    #ifdef serial1    
    Serial.print("\n[Client connected] ");
    #endif

    while (client.connected()){
      
      if (client.available()){

        String line = client.readStringUntil('\r');
       
        app_msg = 0; // will be set in parse_app_msg
 
        parse_app_msg(line); // handle the msg there. send reply to app here
        
        switch (app_msg){

          case 7:   // request status
          
            send_status();

            break;
          case 14:  // scan IP

            ack_scan();
            break;        
        } 
        
        break;
      
      } // if client.available
    }
    
    delay(1); // give the web browser time to receive the data

    client.stop();

    #ifdef serial1    
    Serial.println("[Client disonnected]");
    #endif
    
  }
}

