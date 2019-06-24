#include "include.h"

void Hardware_Init() {
  vTaskDelay(100);
  Serial.begin(115200);
  for (int i = 0; i < RELAY_SIZE; i++) {
    Relay_[i] = new Relay(Relay_PINOUT[i]);
    Relay_Control_.enque(Relay_[i]);
  }

  for (int i = 0; i < ADC_SIZE; i++) {
    adcAttachPin(ADC_PINTOUT[i]);
    adcStart(ADC_PINTOUT[i]);
  }

  pinMode(PIN_WTD, OUTPUT);
  pinMode(CON_LED, OUTPUT);
  pinMode(RUN_LED, OUTPUT);

  IS_EPPROM_OK = EEPROM.begin(EPPROM_SIZE);
}

void Memory_Init() {
  Reset_count = storage.NVS_GetUInt("SYSTEM", "RESET"); Reset_count++;
  storage.NVS_SetUInt("SYSTEM", "RESET", Reset_count);
  Live_time = storage.NVS_GetUInt("SYSTEM", "LIVE_TIME");
  DEVICE = (ISRAR_Device)storage.NVS_GetUInt("SYSTEM", "DEVICE");
  storage.NVS_GetString("SYSTEM", "SERIAL_NUMBER", SERIAL_NUMBER, sizeof(SERIAL_NUMBER));
  uint32_t P = sizeof(Relay_Basic) * ((MAXIMUM_NUMBER_TIME_SCHEDULE * 3) + 6 ); // 6 mix
  EEPROM.get<iStar_Parameters>(P, iStar_Params);
  Memory_temperature_get();
  Serial.println("----------------------------------");
  Serial.println("Reset count: "+String(Reset_count));
  Serial.println("Device: "+ String(DEVICE==iSTAR_DEVICE?String("iSTAR"):String("OTHER")));
  Serial.println("Live time: "+String(Live_time));
  Serial.println("----------------------------------");

  Memory_WIFI_Init();
  Memory_Relay_Init();
  Serial.println("DEVICE->"+String((int)DEVICE));
  if(DEVICE==DEVICE_NONE)
    Relay_Set_Defualt(iSTAR_DEVICE);
  last_device = DEVICE;
}
void Memory_RS485_Init(){
  MB_mode = (Modbus_Mode_)storage.NVS_GetUInt("RS485", "MODE");
  storage.NVS_GetString("RS485", "RS485ID", RS485_SLAVE_ID, sizeof(RS485_SLAVE_ID));
  Memory_RS485_Get_List();
}
void Memory_WIFI_Init() {
  storage.NVS_GetString("WIFI", "SSID", cssid, sizeof(cssid));
  storage.NVS_GetString("WIFI", "PASS", cpass, sizeof(cpass));

}

void Memory_Relay_Init() {
  RELAY_ENABLE = storage.NVS_GetUInt("RELAY", "RELAY_ENABLE");
  for (int i = 0; i < RELAY_SIZE; i++) {
    char c[2] = {i + 0x30, 0};
    TimeSchedule_Set[i] = storage.NVS_GetUInt("RL_SCHEDULE", (const char*) c);
    Serial.println("TimeSchedule_Set_" + String(i) + String(":") + String(TimeSchedule_Set[i]));
    Relay_[i]->Number_Time_Schedule = TimeSchedule_Set[i]; // set number shcedule
    if (IS_EPPROM_OK == true) {
      for (int j=0; j < TimeSchedule_Set[i]; j++) {
        EEPROM.get<Relay_Basic>(sizeof(Relay_Basic) * ((MAXIMUM_NUMBER_TIME_SCHEDULE * i) + j), Relay_[i]->R[j]);
      }
    }
    Relay_[i]->g_reset = true;
    Relay_Time_on[i] =  &Relay_[i]->Time_live_on;
    for (int j = 0; j < MAXIMUM_NUMBER_TIME_SCHEDULE; j++) {
      Relay_[i]->R[j].Condition.on_condition = &iStarMode[i].on_condition;
      Relay_[i]->R[j].Condition.off_condition = &iStarMode[i].off_condition;
      Relay_[i]->R[j].Condition.fail_condition = &iStarMode[i].fail_condition;
      Relay_[i]->R[j].Condition.fail = &iStarMode[i].fail;
      Relay_[i]->R[j].Condition.time_min = &iStarMode[i].time_min;
      Relay_[i]->R[j].Condition.time_max = &iStarMode[i].time_max;
      Relay_[i]->R[j].Condition.time_fail_reset = &iStarMode[i].time_fail_reset;
    }
  }
}

bool Memory_Relay_Schedule_Set(uint8_t R, uint32_t SN) {
  storage.NVS_SetUInt("RL_SCHEDULE", String(R).c_str(), SN);
  uint32_t SS = storage.NVS_GetUInt("RL_SCHEDULE", String(R).c_str());
  if (SS == SN) {
    return true;
  }
  return false;
}

bool Memory_Relay_Set(uint8_t R, uint8_t S, Relay_Basic D) {
  if (IS_EPPROM_OK == true) {
    uint32_t P = sizeof(Relay_Basic) * ((MAXIMUM_NUMBER_TIME_SCHEDULE * R) + S);
    EEPROM.put<Relay_Basic>(P, D);
    return EEPROM.commit();
  }
  return false;
}

bool Memory_RS485_Get_List(){
  for(int i=0; i< RS485_MAX_DEVICE; i++){
    uint32_t P= sizeof(Relay_Basic) * ((MAXIMUM_NUMBER_TIME_SCHEDULE * 3) + 6)+sizeof(iStar_Parameters) + sizeof(RS485_LIST_DEVICE_)*i;
    EEPROM.get<RS485_LIST_DEVICE_>(P, RS485_LIST_DEVICE[i]);
    //Serial.println("id->"+String(RS485_LIST_DEVICE[i].id)+" device->"+String(RS485_LIST_DEVICE[i].DEVICE));
  }
}

bool Memory_RS485_Set_List(){
  for(int i=0; i< RS485_MAX_DEVICE; i++){
    uint32_t P= sizeof(Relay_Basic) * ((MAXIMUM_NUMBER_TIME_SCHEDULE * 3) + 6)+sizeof(iStar_Parameters) + sizeof(RS485_LIST_DEVICE_)*i;
    EEPROM.put<RS485_LIST_DEVICE_>(P, RS485_LIST_DEVICE[i]);
    EEPROM.commit();
  }
}
bool Memory_istar_set(){
   if (IS_EPPROM_OK == true) {
      uint32_t P = sizeof(Relay_Basic) * ((MAXIMUM_NUMBER_TIME_SCHEDULE * 3) + 6); // 6 mix
      EEPROM.put<iStar_Parameters>(P, iStar_Params);
      return EEPROM.commit();
   }
   return false;
}
bool Memory_temperature_set(){
  for(int i=0; i< RELAY_SIZE; i++){
    storage.NVS_SetUInt("RL_TEMPERATURE", String("RL"+String(i)+"TON").c_str(), iStarTemp[i].T_ON);
    storage.NVS_SetUInt("RL_TEMPERATURE", String("RL"+String(i)+"TOFF").c_str(), iStarTemp[i].T_OFF);
  }
}
bool Memory_temperature_get(){
  for(int i=0; i< RELAY_SIZE; i++){
    iStarTemp[i].T_ON = storage.NVS_GetUInt("RL_TEMPERATURE", String("RL"+String(i)+"TON").c_str());
    iStarTemp[i].T_OFF = storage.NVS_GetUInt("RL_TEMPERATURE", String("RL"+String(i)+"TOFF").c_str());
  }
}
bool Relay_Set(uint8_t R, uint8_t S, Relay_Basic D) {
  Relay_[R]->R[S] = D;
  return Memory_Relay_Set(R, S, D);
}

void Relay_Set_Defualt(ISRAR_Device device){
  iStar_Params.Manual = 0;
  iStar_Params.p_Manual = 0;
  if(device==iSTAR_DEVICE || device==DEVICE_NONE){
    DEVICE=iSTAR_DEVICE;
    RELAY_ENABLE = 0;
    iStar_Params.TTMAX = 80;
    iStar_Params.TBMAX = 80;
    iStar_Params.TBS =  50;
    iStar_Params.R_CAP =  0;
    iStar_Params.TANK_VOL =  0;
    Memory_istar_set();
    for(int i=0; i<RELAY_SIZE; i++){
      iStar_Params.p_Manual&=~(1<<i);     // disable device
      Relay_[i]->Number_Time_Schedule = 3;  // reset number time schedule
      Relay_[i]->g_reset= true;             // reset relay basic
      TimeSchedule_Set[i]=3;
      for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
        Relay_[i]->R[j].__Mode = __Mode_None;
        Relay_[i]->R[j].Loop.time_on = j<3?600:0;
        Relay_[i]->R[j].Loop.time_off = j<3?600:0;
        iStarTemp[i].T_ON = 10; //j<3?5:0;
        iStarTemp[i].T_OFF = 5;
      }
      Relay_[i]->R[0].Time_Schedule.timestamp_start = 25200;  // create 3 schedule
      Relay_[i]->R[0].Time_Schedule.duration = 7200;
      Relay_[i]->R[1].Time_Schedule.timestamp_start = 46800;
      Relay_[i]->R[1].Time_Schedule.duration = 7200;
      Relay_[i]->R[2].Time_Schedule.timestamp_start = 68400;
      Relay_[i]->R[2].Time_Schedule.duration = 7200;
      for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++)
        Memory_Relay_Set(i, j, Relay_[i]->R[j]);
      char c[2] = {i + 0x30, 0};
      storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, Relay_[i]->Number_Time_Schedule);
    }
  }else if(device==OTHER){
    DEVICE=OTHER;
    for(int i=0; i<RELAY_SIZE; i++){
      TimeSchedule_Set[i]=0;
      Relay_[i]->Number_Time_Schedule = 0;
      for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
        Relay_[i]->R[j].__Mode = __Mode_None;
        Relay_[i]->R[j].Loop.time_on = 0;
        Relay_[i]->R[j].Loop.time_off = 0;
        iStarTemp[i].T_ON = 0;
        iStarTemp[i].T_OFF = 0;
        Memory_Relay_Set(i, j, Relay_[i]->R[j]);
      }
      char c[2] = {i + 0x30, 0};
      storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, Relay_[i]->Number_Time_Schedule);
    }
  }
  Memory_istar_set();
  Memory_temperature_set();
}

void Timer_Init() {
  xTaskCreate(onTimer, "Timer TASK", 1024, NULL, 12, NULL);
  xTaskCreate(control_Task, "Control TASK", 4096, NULL, 11, NULL);
  // xTaskCreate(MQTT_Task, "MQTT TASK", 8196, NULL, 10, NULL);//
  xTaskCreatePinnedToCore(MQTT_Task, "MQTT TASK", 8196, NULL, 9, NULL, 1); 
  xTaskCreatePinnedToCore(Sensor_Task, "Sensor Task", 1024, NULL, 9, NULL, 1); 
  xTaskCreate(RS485_Task, "RS485 Task", 4096, NULL, 8, NULL);
  
}

void Wifi_Init() {
  Serial.println("wifi: "+String(cssid)+" pass: "+String(cpass));
  wifi_.set(cssid, cpass);
  wifi_.connect();
}

void RTC_Init() {
  uint32_t deltaT;
  if (wifi_.wifi_status == WL_CONNECTED) {
    if (rtc.sync() == true) {
      goto EXT_SYNS;
    } else {
      goto INT_SYNS;
    }
  } else {  //0948
    if (rtc.check() == true) {
      goto  EXT_SYNS;
    } else {
      goto INT_SYNS;
    }
  }
  return;
EXT_SYNS:
  Serial.println("EXT SYNC");
  deltaT = abs((rtc.converToUnixTime() - rtc.converToUnixTime(ext_rtc.get()))); //
  for (int i = 0; i < 3; i++) {
    ext_rtc.setTime(rtc.get());
    if (ext_rtc.check() == true) {
      FAIL_STATUS &= ~EXT_RTC_ERROR;
      return;
    }
    // set error
    FAIL_STATUS |= EXT_RTC_ERROR;
  }
  return;
INT_SYNS:
  Serial.println("INT SYNC");
  if (ext_rtc.check() == true) {
    FAIL_STATUS &= ~EXT_RTC_ERROR;
    rtc.setTime(ext_rtc.get());
    for (int i = 0; i < 3; i++) {
      if (rtc.check() == true)
        return ;
    }
  } else FAIL_STATUS |= EXT_RTC_ERROR;
  return;

}
float get_temp_ntc10k(int port_analog) {
  // Steinhart-Hart variables:
  // www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
  float a = 1.140442647e-3;
  float b = 2.320549520e-4;
  float c = 0.9747106158e-7;
  float val = 0;
  float R, T;
  for (int i = 0; i < 10; i++) {
    val += analogRead(port_analog);
    delayMicroseconds(1);
  }
  val = val / 10;
  val = (val / 4095.0) * 4.192;   // conver to volt
  val = (4.192 - val) * 3300 / val; // conver to R
  T = 1.0 / (a + b * log(val) + c * log(val) * log(val) * log(val));
  return T - 273.15;
}

void iStar_CheckCondition() {
  // Serial.println("TT_MAX->"+String(TT_MAX)+ "TB_MAX->"+String(TB_MAX)+" TCF->"+String(TCF)+" TRF->"+String(TRF));
  if (TT > MIN_TEMP && TT < MAX_TEMP) {
    FAIL_STATUS &= ~TT_ERROR;
    iStarMode[0].on_condition = ((TT - TB) >= TT_ON);
    iStarMode[0].off_condition = ((TT - TB) < TT_OFF);
    iStarMode[0].fail_condition = (TT >= TT_MAX) || (TT-TB>TCF) || (FAIL_STATUS & TB_ERROR != 0);
  } else {
    FAIL_STATUS |= TT_ERROR;
    iStarMode[0].fail_condition = true;
  }

  if (TB > MIN_TEMP && TB < MAX_TEMP) {
    FAIL_STATUS &= ~TB_ERROR;
    iStarMode[1].on_condition = (TB - TH) >= TB_ON;
    iStarMode[1].off_condition = (TB - TH) < TB_OFF;
    iStarMode[1].fail_condition = (TB >= TB_MAX) ||(TB-TH>TRF) || (FAIL_STATUS & TH_ERROR != 0);
  } else {
    FAIL_STATUS |= TB_ERROR;
    iStarMode[1].fail_condition = true;
  }

  static bool is_heater_running = false;

  if (TH > MIN_TEMP && TH < MAX_TEMP) {
    FAIL_STATUS &= ~TH_ERROR;
    iStarMode[2].on_condition = (TB_SET - TB) >= TH_ON;
    iStarMode[2].off_condition = TB > TB_SET;
    iStarMode[2].fail_condition = (TB > TB_MAX) || (FAIL_STATUS & TB_ERROR != 0); //|| 

    // if(iStarMode[2].fail!=0 || iStarMode[2].off_condition==1){
    //   is_heater_running = false;
    // }
    // if(iStarMode[2].on_condition && is_heater_running==false){
    //   is_heater_running = true;
    //   if(iStar_Params.R_CAP!=0)
    //     iStarMode[2].time_max = (int)(iStar_Params.TANK_VOL*1000*4.18*(abs(iStar_Params.TBS-TB)))/(iStar_Params.R_CAP*1000);
    //   storage.NVS_SetUInt("HEATER", "TIME_MAX", iStarMode[2].time_max);
    // }

  } else {
    FAIL_STATUS |= TH_ERROR;
    iStarMode[2].fail_condition = true;
  }

}

