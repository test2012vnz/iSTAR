

void onTimer(void *pvParameters) {
  xTaskCreatePinnedToCore(CON_LED_TASK, "Sensor Task", 1024, NULL, 12, NULL, 1); 
  xTaskCreatePinnedToCore(RUN_LED_TASK, "Sensor Task", 1024, NULL, 12, NULL, 1); 
  for (;;) {
    digitalWrite(PIN_WTD,!digitalRead(PIN_WTD));
    vTaskDelay(500);
  }
}

void RUN_LED_TASK(void *pvParameters) {
  for(;;){
    if((FAIL_STATUS & RL1_OVER_TIME) !=0 ||
       (FAIL_STATUS & RL2_OVER_TIME) !=0 ||
       (FAIL_STATUS & RL3_OVER_TIME) !=0)
      RUN_Status = iRUN_FAIL_TIME;
    if(!IS_DURING_TEST_MODE ){
      switch(RUN_Status){
        case iRUN_Null:{
          
        }break;
        case iRUN_OK:{
          digitalWrite(RUN_LED, HIGH);
        }break;
        case iRUN_FAIL:{
          digitalWrite(RUN_LED, !digitalRead(RUN_LED));
        }break;
        case iRUN_FAIL_TIME:{
          digitalWrite(RUN_LED, HIGH);
          vTaskDelay(250);
          digitalWrite(RUN_LED, LOW);
          vTaskDelay(250);
          digitalWrite(RUN_LED, HIGH);
          vTaskDelay(250);
          digitalWrite(RUN_LED, LOW);
          vTaskDelay(250);
        }break;
      }
    }
    vTaskDelay(1000);
  }
}
void CON_LED_TASK(void *pvParameters) {
  for(;;){
    if(!IS_DURING_TEST_MODE ){
      switch(CON_Status){
        case iCON_Null:{
          
        }break;
        case iCON_Wifi_Fail:{
           digitalWrite(CON_LED, !digitalRead(CON_LED));
        }break;
        case iCON_MQTT_Fail:{
          digitalWrite(CON_LED, HIGH);
          vTaskDelay(250);
          digitalWrite(CON_LED, LOW);
          vTaskDelay(250);
          digitalWrite(CON_LED, HIGH);
          vTaskDelay(250);
          digitalWrite(CON_LED, LOW);
          vTaskDelay(250);
        }break;
        case iCON_OK:{
          digitalWrite(CON_LED, HIGH);
        }break;
      }
    }
    vTaskDelay(1000);
  }
}