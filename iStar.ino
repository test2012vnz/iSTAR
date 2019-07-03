#include "include.h"
void setup() {
  Hardware_Init();
  Memory_Init();
  Webserver_Init();
  Memory_RS485_Init();
  vTaskDelay(3000);
  Timer_Init();
  vTaskDelay(3000);
  Serial.println("START");

/* FOR TEST*/
for(int i=0; i<3; i++){
  Relay_[i]->relay_number = (i+1);
  Relay_[i]->DEBUG_STR.TTAM = &f_ADC[0];
  Relay_[i]->DEBUG_STR.TBON = &f_ADC[1];
  Relay_[i]->DEBUG_STR.THOI = &f_ADC[2];
  Relay_[i]->DEBUG_STR.TBONS = &iStar_Params.TBS;
  for(int j=0; j<5; j++)
    Relay_[i]->R[j].relay_number = (i+1);
}
/**/
}

void loop() {
  server.handleClient();
  webSocket.loop();
  vTaskDelay(10);
}

void control_Task(void *pvParameters) {
  RTC_Init();
  vTaskDelay(7000);
  for (;;) {
    if (rtc.check() == true) {
      SYSTEM_TIME = rtc.getSecondInDay();
      if(SYSTEM_TIME%600==0){
        Live_time+=5;
        storage.NVS_SetUInt("SYSTEM", "LIVE_TIME", Live_time);
      }
      if(SYSTEM_TIME%43200==0){
        wifi_reconnect_count = 0;
        RTC_Init();
      }
      RUN_Status = iRUN_OK;
      // Serial.println("ext rtc->"+String(ext_rtc.getSecondInDay()));
      if(!IS_DURING_TEST_MODE)                  // check test mode
        Relay_Control_.run(SYSTEM_TIME);        ////
      int k = 5;
      for(int i=0; i<3; i++){
        if(iStarMode[i].fail==1){ // fail over time
          FAIL_STATUS |= (1<<(k));
        } else FAIL_STATUS &= ~(1<<(k));
        if(iStarMode[i].fail==2){ // fail
          FAIL_STATUS |= (1<<(k+1));
        } else FAIL_STATUS &= ~(1<<(k+1));
        k+=2;
      }

      FAIL_STATUS &= ~IN_RTC_ERROR;
    } else {
      RUN_Status = iRUN_FAIL;
      // set internal time rr
      FAIL_STATUS |= IN_RTC_ERROR;
      RTC_Init();
      Serial.println("time err");
    }
    vTaskDelay(1000);
  }
}

void MQTT_Task(void *pvParameters) {
  WiFi.setAutoReconnect(0);
  vTaskDelay(1000);
  Wifi_Init();
  MQTT_TASK();
}

void Sensor_Task(void *pvParameters) {
  vTaskDelay(1000);
  for (;;) {
    for (int i = 0; i < ADC_SIZE; i++) {
      f_ADC[i] = get_temp_ntc10k(ADC_PINTOUT[i]);
    }
    // Serial.println("T.TAM->"+String(f_ADC[0])+" T.BON->"+String(f_ADC[1])+"T.HOI->"+String(f_ADC[2]));
    // f_ADC[0] = 70;
    // f_ADC[1] = 60;
    // f_ADC[2] = 50;
    iStar_CheckCondition();
    vTaskDelay(1000);
  }
}

void RS485_Task(void *pvParameters) {
  vTaskDelay(15000);
  for (;;) {
    // Serial.println("rs485_Task->"+String(xPortGetCoreID()));
    switch (MB_mode) {
      case Modbus_Null: {
          vTaskDelay(1000);
        } break;
      case Modbus_Master: {
        Serial.println("MASTER");
        iStar_pkg = create_base_json();
        iStar_pkg = nested_json(iStar_pkg, create_json_frame(),"iStarList");  //
        int count = 0;

        for(int i=0; i<10;i++){
          if(MB_mode!=Modbus_Master){
            Serial.println("swicth to slave");
            goto shared_material;
          }
          if(RS485_LIST_DEVICE[i].id>0){
            count++;
            switch ((int)RS485_LIST_DEVICE[i].RS485_DEVICE) {
                case 0:{  // mfm
                  MFM_ MFM(RS485_LIST_DEVICE[i].id,&rs485);
                  iStar_pkg = nested_json(iStar_pkg, conv_json(MFM.toString()), "MFMList");
                }break;
                case 1:{  // dpm

                }break;
                case 2:{  // sofar
                  Sofar sofar(RS485_LIST_DEVICE[i].id,&rs485);
                  iStar_pkg = nested_json(iStar_pkg, conv_json(sofar.toString()), "SofarList");
                }break;
            }
            vTaskDelay(1000);
          }
        }
        RS485_pkg_ready = true;;
        vTaskDelay(40000);
        } break;
      case Modbus_Slave: {
          RS485_pkg_ready = false;
          MB_SLAVE.process();     // slave
          vTaskDelay(1);
        } break;
      default: {
        shared_material:
          vTaskDelay(1000);
      }
    }
  }
}
