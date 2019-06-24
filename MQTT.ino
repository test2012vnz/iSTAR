// Phap Ha, [14.05.19 15:25]
void MQTT_TASK() {
  String root = SPIFFS_readFile("/ROOTCA.txt");
  String cert = SPIFFS_readFile("/CERTIFICATE.txt");
  String pri = SPIFFS_readFile("/PRIVATEKEY.txt");
  
  httpsClient.setCACert(root.c_str());
  httpsClient.setCertificate(cert.c_str());
  httpsClient.setPrivateKey(pri.c_str());
  mqttClient.setServer(endpoint, 8883);
  mqttClient.setCallback(MQTT_callback);
  String send_pkg="";
  int tick = 0;
  for (;;) {
    // Serial.println("Free heap->"+String(ESP.getFrseeHeap()));
    if (WiFi.status() == WL_CONNECTED){
      if(!mqttClient.connected()){
         CON_Status = iCON_MQTT_Fail;
        connectAWSIoT();
        vTaskDelay(10000);
      }else{
        mqttClient.loop();
        if(millis()/1000 - tick >10){
          if(RS485_pkg_ready==true){
            send_pkg = iStar_pkg;
          }
          else{
              send_pkg = create_base_json();
              send_pkg = nested_json(send_pkg, create_json_frame(),"iStarList");  //
              webSocket.broadcastTXT("log="+send_pkg);
          }
          if(send_pkg!=""){
            webSocket.broadcastTXT("log="+send_pkg);
            mqttClient.publish(pubTopic, send_pkg.c_str());
          }
          tick = millis()/1000;
        }
      }

    } else {
      // mqttClient.disconnect();
      CON_Status = iCON_Wifi_Fail;
      if(!IS_STA_NO_AP)
        Wifi_Init();
      // if(WiFi.status() == WL_CONNECTED)
      //   RTC_Init();
      vTaskDelay(6000);
    }
    vTaskDelay(1000);
  }
}
void get_certificate(){
  String root = SPIFFS_readFile("/ROOTCA.txt");
  String cert = SPIFFS_readFile("/CERTIFICATE.txt");
  String pri = SPIFFS_readFile("/PRIVATEKEY.txt");
  // Serial.println(root.length());
  // Serial.println(cert.length());
  // Serial.println(pri.length());
  memset(rootca,0,sizeof(rootca));
  memset(certificate,0,sizeof(certificate));
  memset(private_key,0,sizeof(private_key));
  memcpy(rootca, root.c_str(), root.length());
  memcpy(certificate, cert.c_str(), cert.length());
  memcpy(private_key,pri.c_str(),pri.length());
}
void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
}
void connectAWSIoT() {
  WiFi.mode(WIFI_AP_STA );
  Serial.println("---------reconnect.---------");
  String clientid = SERIAL_NUMBER + String(random(0, 0xff));
  if(mqttClient.connect(clientid.c_str())) {
      Serial.println("---------Connected.---------");
      int qos = 0;
      mqttClient.subscribe(subTopic, qos);
      Serial.println("Subscribed.");
      CON_Status = iCON_OK;
  } else {
      Serial.println("Failed. Error state="+String(mqttClient.state()));
      vTaskDelay(20000);
  }
}

void MQTT_send_json(){
  String js = create_base_json();
  js = nested_json(js,"[]", "iStarList");
  js = nested_json(js, create_json_frame(), "iStarList");
  Serial.println(js);
  // mqttClient.publish(pubTopic, js.c_str());
}
void MQTT_callback(char* topic, byte* payload, unsigned int length) {

}
// void MQTT_callback(char* topic, byte* payload, unsigned int length) {
//   char *cstring = (char *) payload;
//   // Serial.print("Message arrived [");
//   // Serial.print(topic);
//   // Serial.print("] ");
//   // Serial.println(length);
//   // Serial.println("");
//   memset(proto.data,0,2000);
//   memcpy(proto.data, payload, length);
//   if(proto.decode(Frame_fields,&O)){
//     // Serial.println("----A1: "+String(O.istar->A1));
//     Serial.println("----A2: "+String(O.istar->A2));
//     // Serial.println("----A3: "+String(O.istar->A3));
//     // Serial.println("----A4: "+String(O.istar->A4));
//     Serial.println("----A5: "+String(O.istar->A5));
//     Serial.println("----A6: "+String(O.istar->A6));
//     Serial.println("----A7: "+String(O.istar->A7));
//     Serial.println("----A8: "+String(O.istar->A8,BIN));
//     // Serial.println("----A9: "+String(O.istar->A9));
//     // Serial.println("----A10: "+String(O.istar->A10));
//     // Serial.println("----A11: "+String(O.istar->A11));
//     // Serial.println("----A12: "+String(O.istar->A12));
//     // Serial.println("----A13: "+String(O.istar->A13));
//     // Serial.println("----A14: "+String(O.istar->A14));
//     // Serial.println("----A15: "+String(O.istar->A15));
//     // Serial.println("----A16: "+String(O.istar->A16));//
//     // Serial.println("----A17: "+String(O.istar->A17));
//     // Serial.println("----A18: "+String(O.istar->A18));
//     // Serial.println("----A19: "+String(O.istar->A19));
//     // Serial.println("----A20: "+String(O.istar->A20));
//     // Serial.println("----A21: "+String(O.istar->A21));
//     // Serial.println("----A22: "+String(O.istar->A22));
//     // Serial.println("----A23: "+String(O.istar->A23));
//     // Serial.println("----A24: "+String(O.istar->A24));
//     // Serial.println("----A25: "+String(O.istar->A25));
//     // Serial.println("----A26: "+String(O.istar->A26));
//     // Serial.println("----A27: "+String(O.istar->A27));
//     // Serial.println("----A28: "+String(O.istar->A28));
//     // Serial.println("----A29: "+String(O.istar->A29));
//     // Serial.println("----A30: "+String(O.istar->A30));
//     // Serial.println("----A31: "+String(O.istar->A31));
//     // Serial.println("----A32: "+String(O.istar->A32));
//     // Serial.println("----A33: "+String(O.istar->A33));
//     // Serial.println("----A34: "+String(O.istar->A34));
//     // Serial.println("----A35: "+String(O.istar->A35));
//     // Serial.println("----A36: "+String(O.istar->A36));//
//     // Serial.println("----A37: "+String(O.istar->A37));
//     if(O.istar->A2==1){ // auto / manual
//       iStar_Params.Manual = 1;
//     }
//     else iStar_Params.Manual = 0;
//     O.istar->A5?iStar_Params.p_Manual|=(1<<0):iStar_Params.p_Manual&=~(1<<0);
//     O.istar->A6?iStar_Params.p_Manual|=(1<<1):iStar_Params.p_Manual&=~(1<<1);
//     O.istar->A7?iStar_Params.p_Manual|=(1<<2):iStar_Params.p_Manual&=~(1<<2);
//     for(int i=0; i<RELAY_SIZE; i++){
//       if(O.istar->A2==1){
//         Relay_[i]->Number_Time_Schedule = 1;
//         Relay_[i]->R[0].__Mode=__Mode_Manual;
//         if(iStar_Params.p_Manual&(1<<i))
//           Relay_[i]->R[0].Manual_Control = true;
//         else
//           Relay_[i]->R[0].Manual_Control = false;
//       }
//       Memory_Relay_Set(i, 0, Relay_[i]->R[0]);
//       char c[2] = {i + 0x30, 0};
//       storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, Relay_[i]->Number_Time_Schedule);
//     }
//     Memory_istar_set();
//   }
// }
String SPIFFS_readFile(const char* fileName){
  String str="";
  if(SPIFFS.begin(true)){
    File file = SPIFFS.open(fileName, "r");
    if(!file){
      //Serial.println("Failed to open file for reading");
    }else{
      //Serial.println("File  length->"+String(file.size()));
      while(file.available()){
        str+=char(file.read());
      }
      file.close();
    }
  }
  return str;
}
int  SPIFFS_writeFile(const char* fileName, String payload){
  File file = SPIFFS.open(fileName, FILE_WRITE);
  if(!file){
     //Serial.println("There was an error opening the file for writing");
  }else{
    if(file.print(payload)){
      file.close();
       return 1;
    }
  }
  return 0;
}
void str2chrArr(String str, char *a) {
  str.toCharArray(a, 50); // MAX LENGHT 50
}
String get_Relay_Schedule_str(int i){
  String str= "";
  for(int j=0; j<5; j++){
    str+=String(Relay_[i]->R[j].Time_Schedule.timestamp_start/3600)+":";
    str+=String(Relay_[i]->R[j].Time_Schedule.timestamp_start%3600/60)+"-";
    str+=String((Relay_[i]->R[j].Time_Schedule.timestamp_start+Relay_[i]->R[j].Time_Schedule.duration)/3600)+":";
    str+=String((Relay_[i]->R[j].Time_Schedule.timestamp_start+Relay_[i]->R[j].Time_Schedule.duration)%3600/60)+"/";
  }
  return str.substring(0,str.length()-1);
}
String get_Relay_Loop_str(int i){
  String str="";
  for(int j=0; j<5; j++){
    str+=String(Relay_[i]->R[j].Loop.time_on/60)+":";
    str+=String(Relay_[i]->R[j].Loop.time_off/60)+"/";
  }
  return str.substring(0,str.length()-1);
}

String create_json_frame(){
  String json = "";
  json+= "{\"serial\":\""+ String(SERIAL_NUMBER)+"\",";
  json+= "\"iStarID\":" + String(0) +",";
  json+= "\"status\":" + String(0) +",";
  json+= "\"A1\":" + String(DEVICE) +",";
  json+= "\"A2\":" + String(iStar_Params.Manual) +",";
  json+= "\"A3\":" + String(Reset_count) + ",";
  json+= "\"A4\":" + String(Live_time) + ",";
  json+= "\"A5\":" + String(digitalRead(PIN_RELAY_1)) + ",";
  json+= "\"A6\":" + String(digitalRead(PIN_RELAY_2)) + ",";
  json+= "\"A7\":" + String(digitalRead(PIN_RELAY_3)) + ",";
  json+= "\"A8\":" + String(FAIL_STATUS) + ",";
  json+= "\"A9\":" + String(iStar_Params.TBS) + ",";
  json+= "\"A10\":" + String(iStar_Params.TTMAX) + ",";
  json+= "\"A11\":" + String(iStar_Params.TBMAX) + ",";
  json+= "\"A12\":" + String(TCF) + ",";
  json+= "\"A13\":" + String(TRF) + ",";
  json+= "\"A14\":" + String(iStar_Params.R_CAP) + ",";
  json+= "\"A15\":" + String(iStar_Params.TANK_VOL) + ",";
  json+= "\"A16\":\"" + String(String(SYSTEM_TIME/3600)+":"+String(SYSTEM_TIME%3600/60)) + "\",";
  json+= "\"A17\":" + String(TT) + ",";
  json+= "\"A18\":" + String(TB) + ",";
  json+= "\"A19\":" + String(TH) + ",";
  json+= "\"A20\":" + String(TimeSchedule_Set[RELAY_1]) + ",";
  json+= "\"A21\":" + String(TimeSchedule_Set[RELAY_2]) + ",";
  json+= "\"A22\":" + String(TimeSchedule_Set[RELAY_3]) + ",";
  json+= "\"A23\":\"" + get_Relay_Schedule_str(RELAY_1) + "\",";
  json+= "\"A24\":\"" + get_Relay_Schedule_str(RELAY_2) + "\",";
  json+= "\"A25\":\"" + get_Relay_Schedule_str(RELAY_3) + "\",";
  json+= "\"A26\":\"" + get_Relay_Loop_str(RELAY_1) + "\",";
  json+= "\"A27\":\"" + get_Relay_Loop_str(RELAY_2) + "\",";
  json+= "\"A28\":\"" + get_Relay_Loop_str(RELAY_3) + "\",";
  json+= "\"A29\":" + String(iStarTemp[RELAY_1].T_ON) + ",";
  json+= "\"A30\":" + String(iStarTemp[RELAY_1].T_OFF) + ",";
  json+= "\"A31\":" + String(iStarTemp[RELAY_2].T_ON) + ",";
  json+= "\"A32\":" + String(iStarTemp[RELAY_2].T_OFF) + ",";
  json+= "\"A33\":" + String(iStarTemp[RELAY_3].T_ON) + ",";
  json+= "\"A34\":" + String(iStarMode[1].time_fail_reset) + ",";
  json+= "\"A35\":" + String(iStarMode[1].time_max) + ",";
  json+= "\"A36\":" + String(iStarMode[1].time_min);
  json+= "}";
  return json;
}
// void MQTT_send_packed(){
//   // F.istar = &IstarProto;
//   IstarProto.A1 = DEVICE; //device
//   IstarProto.A2 = iStar_Params.Manual; //auto / manual
//   IstarProto.A3 = Reset_count;
//   IstarProto.A4 = Live_time;
//   IstarProto.A5 = digitalRead(PIN_RELAY_1);
//   IstarProto.A6 = digitalRead(PIN_RELAY_2);
//   IstarProto.A7 = digitalRead(PIN_RELAY_3);
//   IstarProto.A8 = FAIL_STATUS;
//   IstarProto.A9 = iStar_Params.TBS;
//   IstarProto.A10 = iStar_Params.TTMAX;
//   IstarProto.A11 = iStar_Params.TBMAX;
//   IstarProto.A12 = TCF;
//   IstarProto.A13 = TRF;
//   IstarProto.A14 = iStar_Params.R_CAP;
//   IstarProto.A15 = iStar_Params.TANK_VOL;
//   str2chrArr(String(String(SYSTEM_TIME/3600)+":"+String(SYSTEM_TIME%3600/60)), IstarProto.A16);
//   IstarProto.A17 = TT;
//   IstarProto.A18 = TB;
//   IstarProto.A19 = TH;
//   IstarProto.A20 = TimeSchedule_Set[RELAY_1];
//   IstarProto.A21 = TimeSchedule_Set[RELAY_2];
//   IstarProto.A22 = TimeSchedule_Set[RELAY_3];
//   str2chrArr(get_Relay_Schedule_str(RELAY_1) ,IstarProto.A23);
//   str2chrArr(get_Relay_Schedule_str(RELAY_2) ,IstarProto.A24);
//   str2chrArr(get_Relay_Schedule_str(RELAY_3) ,IstarProto.A25);
//   str2chrArr(get_Relay_Loop_str(RELAY_1) ,IstarProto.A26);
//   str2chrArr(get_Relay_Loop_str(RELAY_2) ,IstarProto.A27);
//   str2chrArr(get_Relay_Loop_str(RELAY_3) ,IstarProto.A28);
//   IstarProto.A29 = iStarTemp[RELAY_1].T_ON;
//   IstarProto.A30 = iStarTemp[RELAY_1].T_OFF;
//   IstarProto.A31 = iStarTemp[RELAY_2].T_ON;
//   IstarProto.A32 = iStarTemp[RELAY_2].T_OFF;
//   IstarProto.A33 = iStarTemp[RELAY_3].T_ON;
//   IstarProto.A34 = iStarMode[1].time_fail_reset;
//   IstarProto.A35 = iStarMode[1].time_max;
//   IstarProto.A36 = iStarMode[1].time_min;
  // Serial.println("proto lenght->"+String(proto.length));
  // Serial.println("proto data->"+String((char*)proto.data));
  // proto.encode(Frame_fields, &F);
  // PubClient.publish(MQTT_Public_Topic.c_str(), (char*)proto.data, proto.length);
// }
String create_base_json(){
  String js = "";
  js+= "{\"Serial\":\"" +String(SERIAL_NUMBER) + "\",";
  js+= "\"Reset_Count\":\"" +String(Reset_count) +"\",";
  js+= "\"Free_Ram\":\"" + String(ESP.getFreeHeap()) + "\",";
  js+= "\"Communication\":[{\"WIFI\":" + String(toWiFiQuality(WiFi.RSSI())) +",";
  js+= "\"Ethernet\":" + String(1) +",";
  js+= "\"GSM\":" + String(0) +"}],";
  js+= "\"Version\":\"" + String(FW_VERSION) + "\",";
  js+= "\"INTemp\":" + String(45) +"}";
  return js;
}
