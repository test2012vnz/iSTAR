

void onTimer(void *pvParameters) {
  for (;;) {
    if(!IS_DURING_TEST_MODE ){
      digitalWrite(PIN_WTD,!digitalRead(PIN_WTD));
      switch(CON_Status){
        case iCON_Null:{
          
        }break;
        case iCON_Wifi_Fail:{
           digitalWrite(CON_LED, !digitalRead(CON_LED));
           vTaskDelay(500);
           digitalWrite(CON_LED, !digitalRead(CON_LED));
          
        }break;
        case iCON_MQTT_Fail:{
          digitalWrite(CON_LED, !digitalRead(CON_LED));
        }break;
        case iCON_OK:{
          digitalWrite(CON_LED, HIGH);
        }break;
      }
      switch(RUN_Status){
        case iRUN_Null:{
          
        }break;
        case iRUN_OK:{
          digitalWrite(RUN_LED, HIGH);
        }break;
        case iRUN_FAIL:{
          digitalWrite(RUN_LED, !digitalRead(RUN_LED));
        }break;
      }
    }
    vTaskDelay(1000);
  }
}

void ledblink(int cycle){

}