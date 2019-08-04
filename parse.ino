
// this file is the same in simple_wifi and wifi_AP

void parse_app_msg(String pay){

  /*
   *    every message consists of: type, num_tokens. in this simple example, num_tokens is always 0, so I should have simplified further, but I didn't because reasons. and later on we can use num_tokens>0 and have fun
   *    
   *      if num_tokens > 0 then that many should follow.
   * 
   *    
   *    7 0 = query esp status
   *    
   *    
   */

  char * paych = strdup(&pay[0]); // strdup copies pay, and needs to be freed when done
   
  char * save_paych = paych; // save so i can free, which requires original pointer value, and strsep alters paych

  char * token;

  uint16_t data;

  if (strlen(paych) > 0){
#ifdef serial1
    lf();
    Serial.print(" raw msg ");
    Serial.println(paych);
    
#endif

    token = strsep(&paych," ");

    if (strlen(token) > 0){
   
      app_msg = atoi(token);
#ifdef serial1
      Serial.print(" msg ");
      Serial.print(app_msg);
#endif
      
    }
  }
  
  if (strlen(paych) > 0){
#ifdef serial1
    lf();
    Serial.print(" raw msg ");
    Serial.println(paych);
    
#endif
    
    token = strsep(&paych," ");

    if (strlen(token) > 0){
   
      data = atoi(token);

#ifdef serial1
      Serial.print(" data ");
      Serial.print(data);
#endif
       
    }
  }

  free(save_paych);
}
