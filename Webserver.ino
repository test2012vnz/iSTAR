
String response_ISTAR(){
  String js = "{";
  js += "\"PRODUCT\":" + String(1) + ",";
  js += "\"SERIAL_NUMBER\":\"" + String(SERIAL_NUMBER) + "\",";
  js += "\"RS485\":{\"MODE\":"+ String((int)MB_mode) + ",";
  js += "\"SLAVE_ID\":\""+ String(RS485_SLAVE_ID) + "\",";
  js += "\"DEVICES\":[";
  int count = 0;
  for(int i=0; i<RS485_MAX_DEVICE; i++){
    if(RS485_LIST_DEVICE[i].id>0){
      js+= String(RS485_LIST_DEVICE[i].id) +",";
      js+= String((int)RS485_LIST_DEVICE[i].RS485_DEVICE) +",";
      count++;
    }
  }
  if(count!=0)
    js = js.substring(0, js.length()-1);
  js+= "],";
  js+= "\"NUM\":" + String(count)+"},";
  js+= "\"SYSTEM\":{\"TIME\":0,";
  js+= "\"TBS\":" + String(iStar_Params.TBS) + ",";
  js+= "\"TT_MAX\":" + String(iStar_Params.TTMAX)+ ",";
  js+= "\"TBON_MAX\":" + String(iStar_Params.TBMAX)+",";
  js+= "\"RCAP\":"+String(iStar_Params.R_CAP)+",";
  js+= "\"TANK_VOL\":"+ String(iStar_Params.TANK_VOL)+",";
  js+= "\"RELAY_EN\":"+ String(RELAY_ENABLE)+"},";
  js+= "\"CONV\":{\"TYPE\":" + String((int)Relay_[RELAY_1]->R[0].__Mode)+",";
  js+= "\"TON\":" + String(iStarTemp[RELAY_1].T_ON)+",";
  js+= "\"TOFF\":" + String(iStarTemp[RELAY_1].T_OFF)+",";
  js+= "\"TIMEON\":" + String(Relay_[RELAY_1]->R[0].Loop.time_on) + ",";
  js+= "\"TIMEOFF\":" + String(Relay_[RELAY_1]->R[0].Loop.time_off) + "},";
  js+= "\"RETURN\":{\"TYPE\":" + String((int)Relay_[RELAY_2]->R[0].__Mode) + ",";
  js+= "\"TON\":" + String(iStarTemp[RELAY_2].T_ON) + ",";
  js+= "\"TOFF\":" + String( iStarTemp[RELAY_2].T_OFF) + ",";
  js+= "\"TIMEON\":" + String(Relay_[RELAY_2]->R[0].Loop.time_on) + ",";
  js+= "\"TIMEOFF\":" + String(Relay_[RELAY_2]->R[0].Loop.time_off) + "},";
  js+= "\"HEATER\":{\"TON\":" + String(iStarTemp[RELAY_3].T_ON) + "},";
  js+= "\"TIMECHEDULE\":{\"NUM\":" + String(TimeSchedule_Set[0]) + ",";
  js+= "\"SCHEDULE\":[";
  for(int i = 0; i<5; i++){
    js+= String(Relay_[RELAY_2]->R[i].Time_Schedule.timestamp_start)+",";
    js+= String(Relay_[RELAY_2]->R[i].Time_Schedule.duration)+",";
  }
  js = js.substring(0, js.length()-1);
  js+="]}}";
  return js;
}
String response_OTHER(){
  String js= "{\"PRODUCT\":2,";
  js += "\"SERIAL_NUMBER\":\"" + String(SERIAL_NUMBER)+"\",";
  js += "\"RS485\":{\"MODE\":" + String((int)MB_mode) +",";
  js += "\"SLAVE_ID\":\"" + String(RS485_SLAVE_ID) + "\",";
  js += "\"DEVICES\":[";
  int count = 0;
  for(int i=0; i<RS485_MAX_DEVICE; i++){
    if(RS485_LIST_DEVICE[i].id>0){
      js+= String(RS485_LIST_DEVICE[i].id) +",";
      js+= String((int)RS485_LIST_DEVICE[i].RS485_DEVICE) +",";
      count++;
    }
  }
  if(count!=0)
    js = js.substring(0, js.length()-1);
  js += "],\"NUM\":" +String(count) + "},";
  js += "\"MANUAL\":"+String(iStar_Params.Manual)+",";
  js += "\"MANUALDATA\":"+String(iStar_Params.p_Manual)+",";
  js += "\"OTHERSLOT\":[";
  for(int relay_num=0; relay_num<RELAY_SIZE; relay_num++){
    js += "{";
    js += "\"NUM\":" +String(Relay_[relay_num]->Number_Time_Schedule)+",";
    js += "\"SLOT\":[";
    for(int i=0; i<MAXIMUM_NUMBER_TIME_SCHEDULE; i++){
      js +="{";
      js += "\"TYPE\":" + String((int)Relay_[relay_num]->R[i].__Mode) +",";
      js += "\"TIMESTAR\":" + String(Relay_[relay_num]->R[i].Time_Schedule.timestamp_start) +",";
      js += "\"DURATION\":" + String(Relay_[relay_num]->R[i].Time_Schedule.duration) +",";
      js += "\"TIMEON\":"+ String(Relay_[relay_num]->R[i].Loop.time_on) +",";
      js += "\"TIMEOFF\":" + String(Relay_[relay_num]->R[i].Loop.time_off);
      js +="},";
    }
    js = js.substring(0, js.length()-1);
    js += "]},";
  }
  js = js.substring(0, js.length()-1);
  js+="]}";

  return js;
}
void Webserver_Init(){
  WiFi.onEvent(WiFiEvent);
  Serial.println("WIFI MODE->"+String(WiFi.getMode()));
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect(true);                     // disconnects STA Mode
  vTaskDelay(1000);
  WiFi.softAPdisconnect(true);           // disconnects AP Mode 
  vTaskDelay(1000);  

  if(String(SERIAL_NUMBER)!="")
    WiFi.softAP(SERIAL_NUMBER, "12345678");
  else{
    WiFi.softAP("iSTAR new device", "12345678");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  // WiFi.softAPsetHostname("esp32");

  server.on("/", HTTP_GET, [](){
    if(currentuser){
        if(!handleFileRead("/main.html")) server.send(404, "text/plain", "FileNotFound");
    }else{
        if(!handleFileRead("/login.html.gz")) server.send(404, "text/plain", "FileNotFound");
    }
  });
  server.on("/main.css", HTTP_GET, [](){
        if(!handleFileRead("/main.css")) server.send(404, "text/plain", "FileNotFound");
  });
  server.on("/main.js", HTTP_GET, [](){
        if(!handleFileRead("/main.js")) server.send(404, "text/plain", "FileNotFound");
  });

  server.on("/c", serviceEvent);
  server.on("/update", HTTP_POST, []() {
    Serial.println("OKOKOKKOK");
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (OTAUpdate.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.setDebugOutput(true);
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!OTAUpdate.begin()) { //start with max available size
        OTAUpdate.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (OTAUpdate.write(upload.buf, upload.currentSize) != upload.currentSize) {
        OTAUpdate.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (OTAUpdate.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        server.send(200, "text/plain", (OTAUpdate.hasError()) ? "FAIL" : "OK");
      } else {
        OTAUpdate.printError(Serial);
      }
      Serial.setDebugOutput(false);
    }
  });
  server.begin();
  SPIFFS.begin(true);
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  vTaskDelay(1000);
}

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (event == SYSTEM_EVENT_STA_DISCONNECTED) {
    if (info.disconnected.reason == WIFI_REASON_NO_AP_FOUND) {
      Serial.println("---WIFI_REASON_NO_AP_FOUND---");
      IS_STA_NO_AP = true;
    }
  }
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
        Serial.println("["+String(num)+"] -----Disconnected!");
        break;
    case WStype_CONNECTED:
        {
          IPAddress ip = webSocket.remoteIP(num);
          String c_ip = String(ip[0])+":"+String(ip[1])+":"+String(ip[2])+":"+String(ip[3]);
          String str = "pkg="+create_socket_json();
          Serial.println("["+String(num)+"] -----Connected from "+c_ip);
          webSocket.sendTXT(num, "ips="+c_ip);
          webSocket.broadcastTXT("ipa="+c_ip);
          webSocket.broadcastTXT(str);
        }
        break;
    case WStype_TEXT:{
        String JSON = (char *)payload;
        Serial.println(JSON);
        JsonObject&  root = jsonBuffer.parseObject(JSON);
        if(root.containsKey("TEST_MODE")){
          IS_DURING_TEST_MODE = root["TEST_MODE"].as<int>();
          if(root["TEST_MODE"].as<int>()){
            digitalWrite(PIN_RELAY_1, LOW);
            digitalWrite(PIN_RELAY_2, LOW);
            digitalWrite(PIN_RELAY_3, LOW);
            digitalWrite(CON_LED, 0);
            digitalWrite(RUN_LED, 0);
          }
        }
        else if(root.containsKey("TEST") && IS_DURING_TEST_MODE){
          if(root["TEST"]=="LED"){
            if(root["NUM"].as<int>()==1)
              digitalWrite(CON_LED, root["STATE"].as<int>());
            else if(root["NUM"].as<int>()==2)
              digitalWrite(RUN_LED, root["STATE"].as<int>());
          }
          else if(root["TEST"]=="RL"){
            if(root["NUM"].as<int>()==1)
              digitalWrite(PIN_RELAY_1, root["STATE"].as<int>()?HIGH:LOW);
            else if(root["NUM"].as<int>()==2)
              digitalWrite(PIN_RELAY_2, root["STATE"].as<int>()?HIGH:LOW);
            else if(root["NUM"].as<int>()==3)
              digitalWrite(PIN_RELAY_3, root["STATE"].as<int>()?HIGH:LOW);
          }
          else if(root["TEST"]=="ADC"){
            String mess = "{\"ADC\":["+
            mess += String(get_temp_ntc10k(ADC_PINTOUT[0])) +",";
            mess += String(get_temp_ntc10k(ADC_PINTOUT[1])) +",";
            mess += String(get_temp_ntc10k(ADC_PINTOUT[2]))+"]}";
          }
        }
        else if(root.containsKey("UPDATE_FIRMWARE")){
          Serial.println("----ota-----");
          t_httpUpdate_return ret = box.ota(root["UPDATE_FIRMWARE"]);
          switch (ret) {
            case HTTP_UPDATE_FAILED:
              Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
              break;
            case HTTP_UPDATE_NO_UPDATES:
              Serial.println("HTTP_UPDATE_NO_UPDATES");
              break;
            case HTTP_UPDATE_OK:
              Serial.println("HTTP_UPDATE_OK");
              break;
          }
        } 
        else if(root.containsKey("FIRMWARE")){
          if(root["FIRMWARE"]=="GET"){
            Serial.println("---CHEECK FIRRMWWARE");
            if(http.begin("https://api.dropboxapi.com/2/files/list_folder")){
              http.addHeader("Authorization", "Bearer "+String(Bearer));
              http.addHeader("Content-Type", "application/json");
              int httpResponseCode = http.POST("{\"path\":\"/ota\"}");
              String response = http.getString();
              JsonObject&  root = jsonBuffer.parseObject(response); 

              String js = "{\"entries\":[";
              Serial.println("---CHEECK response size->"+String(root["entries"].size()));
              for(int i=0; i<root["entries"].size(); i++){
                String str_slot = root["entries"][i];
                JsonObject&  slot = jsonBuffer.parseObject(str_slot);
                String name = slot["name"];
                String client_modified = slot["client_modified"];
                js+= "{\"name\":\""+ name +"\",\"client_modified\":\""+ client_modified +"\"},";
              }
              js = js.substring(0, js.length()-1);
              js+="]}";
               webSocket.sendTXT(num, "FIRM="+js);
            }else{
            }
          }
          // if(!http.begin(endpoint))
        }
        else if(root.containsKey("ADMIN")){
          int i = root["ADMIN"].as<int>();
          switch (i) {
              case 1:{ // check pcf
                webSocket.sendTXT(num, "admin="+String(ext_rtc.getSecondInDay()));
              }break;
              case 2:{ // set rtc

                  for(int i=0; i<5; i++){
                    ext_rtc.setTime(rtc.get());
                    if(ext_rtc.check() && (ext_rtc.readStatus1()==0))
                      break;
                  }

              }break;
          }
        }
        webSocket.broadcastTXT("message here");
      } break;
  case WStype_ERROR:      
  case WStype_FRAGMENT_TEXT_START:
  case WStype_FRAGMENT_BIN_START:
  case WStype_FRAGMENT:
  case WStype_FRAGMENT_FIN:
    break;
  }

}
void serviceEvent(){
  int m = server.arg("m").toInt();
  String response="";
  switch(m){  // cookie
    case 0:{ 
      String user = server.arg("user");
      if(user == "bWFudQ=="){
        currentuser = Manu_USER;
        response = "login";
      }
      else if(user == "aW5zdA=="){
        currentuser = Installer_USER;
            response = "login";
      } else{
        response = "err";
      }
      server.send(200, "text/plain", response);
    }break;
    case 1:{  // login
      String user = server.arg("user");
      String pass = server.arg("pass");
      if(user == "manu" && pass == "13579"){
        currentuser = Manu_USER;
        response = "bWFudQ==";
      }else if(user == "inst" && pass == "97531"){
        currentuser = Installer_USER;
        response = "aW5zdA==";
      }
      else{
        response = "err";
      }
      server.send(200, "text/plain", response);
    }break;
    case 2:{
          Serial.println("Scanning");
          IS_WIFI_SCANNING=true;
          int8_t nn = WiFi.scanNetworks(false, true);
          response = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
          response += "<wifi>";
          for (uint8_t i = 0; i < nn; i++)
          {
            String ssid = WiFi.SSID(i);
            ssid.replace("<","");
            ssid.replace(">","");
            unsigned int rssi = toWiFiQuality(WiFi.RSSI(i));
            if (ssid.length() == 0){
              ssid = "?";
            }
            response += "<net>";
            response += "<ssid>" + String(ssid) + "</ssid>";
            response += "<rssi>" + String(rssi) + "</rssi>";
            response += "</net>";
          }
          response += "</wifi>";

          IS_WIFI_SCANNING=false;
          // Serial.println(response);
          server.send(200, "text/xml", response);
    }break;
      case 3:{  // connect wifi
          Serial.println("Conect wifi");
          String StrSSID = server.arg("SSID");
          String StrPASS = server.arg("PASS");
          char cSSID[StrSSID.length() + 1];
          char cPASS[StrPASS.length() + 1];
          memset(cSSID, 0, sizeof(cSSID));
          memset(cPASS, 0, sizeof(cPASS));
          StrSSID.toCharArray(cSSID, sizeof(cSSID));
          StrPASS.toCharArray(cPASS, sizeof(cPASS));
          storage.NVS_SetString("WIFI", "SSID", cSSID);
          storage.NVS_SetString("WIFI", "PASS", cPASS);
          memset(cssid, 0, 64);
          memset(cpass, 0, 64);
          storage.NVS_GetString("WIFI", "SSID", cssid, sizeof(cssid));
          storage.NVS_GetString("WIFI", "PASS", cpass, sizeof(cpass));
          WiFi.disconnect();
          IS_WIFI_SETTING = true;
          IS_STA_NO_AP = false;
          wifi_reconnect_count = 0;
          response = "update";
          server.send(200, "text/plain", response);
      }break;
      case 4:{  // device setting
        String JSON = server.arg("JSON");
        JsonObject&  root = jsonBuffer.parseObject(JSON);

        int hh = root["HOUR"].as<int>();
        int mm = root["MINUTE"].as<int>();
        int sec = root["SEC"].as<int>();
        int wday = root["WDAY"].as<int>();
        int day = root["DAY"].as<int>();
        int mon = root["MONTH"].as<int>();
        int y = root["YEAR"].as<int>();
        Serial.println("sv->"+String(hh)+":"+String(mm)+":"+String(sec));
        Serial.println("sv->"+String(day)+"/"+String(mon)+"/"+String(y));
        for(int i=0; i<5; i++){
          ext_rtc.setTime(day, mon, (y%100), wday, hh, mm, sec);
          if(ext_rtc.check() && (ext_rtc.readStatus1()==0))
            break;
        }
        if(ext_rtc.check())
          response="update";
        else response="err";
        server.send(200, "text/plain", response);
      }
      case 5:{  // istar parameters
          String JSON = server.arg("JSON");
          JsonObject&  root = jsonBuffer.parseObject(JSON);

          iStar_Params.TTMAX = root["TTAM_MAX"].as<int>();
          iStar_Params.TBMAX = root["TBON_MAX"].as<int>();
          iStar_Params.TBS = root["TBS"].as<int>();
          iStar_Params.R_CAP = root["R_CAP"].as<int>();
          iStar_Params.TANK_VOL = root["TANK_VOL"].as<int>();

          response = "update";
          Memory_istar_set();
          server.send(200, "text/plain", response);
      }break;
      case 6:{  // rl1
        iStar_Params.Manual = 0;
        if(DEVICE==iSTAR_DEVICE){
          JsonObject&  root = jsonBuffer.parseObject(server.arg("JSON"));
          if(root["EN"].as<int>()==1){
            RELAY_ENABLE |= (1<<RELAY_1);
            if(root["TYPE"].as<int>()==1){
              Relay_[RELAY_1]->Number_Time_Schedule = 5;    // set 5 schedules 1
              iStarTemp[RELAY_1].T_ON = root["TON"].as<int>();;
              iStarTemp[RELAY_1].T_OFF = root["TOFF"].as<int>();
              Memory_temperature_set();
              for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
                Relay_[RELAY_1]->R[j].__Mode=(__Config_Mode_Enum)root["TYPE"].as<int>();
                Relay_[RELAY_1]->R[j].Time_Schedule.timestamp_start = 0;
                Relay_[RELAY_1]->R[j].Time_Schedule.duration = 86400;     // set duaration 24/24
                Memory_Relay_Set(RELAY_1, j, Relay_[RELAY_1]->R[j]);
              }
            }else if(root["TYPE"].as<int>()==2){
              for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
                Relay_[RELAY_1]->R[j].__Mode=(__Config_Mode_Enum)root["TYPE"].as<int>();
                Relay_[RELAY_1]->Number_Time_Schedule = TimeSchedule_Set[0];
                Relay_[RELAY_1]->R[j].Loop.time_on = root["TIMEON"].as<int>();
                Relay_[RELAY_1]->R[j].Loop.time_off = root["TIMEOFF"].as<int>();
                Relay_[RELAY_1]->R[j].Time_Schedule.timestamp_start = Relay_[RELAY_2]->R[j].Time_Schedule.timestamp_start;
                Relay_[RELAY_1]->R[j].Time_Schedule.duration = Relay_[RELAY_2]->R[j].Time_Schedule.duration;
                Memory_Relay_Set(RELAY_1, j, Relay_[RELAY_1]->R[j]);
              }
            }
          }
          else{
            RELAY_ENABLE &= ~(1<<RELAY_1);
            for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
              Relay_[RELAY_1]->R[j].__Mode=__Mode_None;
              Memory_Relay_Set(RELAY_1, j, Relay_[RELAY_1]->R[j]);
            }
          }
          storage.NVS_SetUInt("RELAY", "RELAY_ENABLE", RELAY_ENABLE);
          server.send(200, "text/plain", response_ISTAR());
        }else if(DEVICE==OTHER){
          if(Relay_[RELAY_1]->R[0].__Mode==__Mode_Manual)
            Relay_Set_Defualt(DEVICE);
          JsonObject&  root = jsonBuffer.parseObject(server.arg("JSON"));

          TimeSchedule_Set[RELAY_1]  = root["NUM"].as<int>();
          Relay_[RELAY_1]->Number_Time_Schedule = root["NUM"].as<int>();
        
          for(int j=0; j<TimeSchedule_Set[RELAY_1]; j++){
            String str_slot = root["SLOT"][j];
            JsonObject&  slot = jsonBuffer.parseObject(str_slot);

            Relay_[RELAY_1]->R[j].__Mode=(__Config_Mode_Enum)slot["TYPE"].as<int>();
            Relay_[RELAY_1]->R[j].Time_Schedule.timestamp_start = slot["TIMESTART"].as<int>();
            Relay_[RELAY_1]->R[j].Time_Schedule.duration = slot["DURATION"].as<int>();
            Relay_[RELAY_1]->R[j].Loop.time_on = slot["TIMEON"].as<int>();
            Relay_[RELAY_1]->R[j].Loop.time_off = slot["TIMEOFF"].as<int>();
            Memory_Relay_Set(RELAY_1, j, Relay_[RELAY_1]->R[j]);
          }
          char c[2] = {0 + 0x30, 0};
          storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, TimeSchedule_Set[RELAY_1]);
          server.send(200, "text/plain", response_OTHER());
        }
      }break;
      case 7:{  // rl2
        iStar_Params.Manual = 0;
        if(DEVICE==iSTAR_DEVICE){
          String JSON = server.arg("JSON");
          JsonObject&  root = jsonBuffer.parseObject(JSON);
          if(root["EN"].as<int>()==1){
            RELAY_ENABLE |= (1<<RELAY_2);
            if(root["TYPE"].as<int>()==1){
              iStarTemp[RELAY_2].T_ON = root["TON"].as<int>();
              iStarTemp[RELAY_2].T_OFF = root["TOFF"].as<int>();
              Memory_temperature_set();   
              for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++) {
                Relay_[RELAY_2]->R[j].__Mode=(__Config_Mode_Enum)root["TYPE"].as<int>();
                Memory_Relay_Set(RELAY_2, j, Relay_[RELAY_2]->R[j]);     
              }
            }
            else if(root["TYPE"].as<int>()==2){
              for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
                Relay_[RELAY_2]->R[j].__Mode=(__Config_Mode_Enum)root["TYPE"].as<int>();
                Relay_[RELAY_2]->R[j].Loop.time_on = root["TIMEON"].as<int>();
                Relay_[RELAY_2]->R[j].Loop.time_off = root["TIMEOFF"].as<int>();
                Memory_Relay_Set(RELAY_2, j, Relay_[RELAY_2]->R[j]);
              }
            }
          }
          else{
            RELAY_ENABLE &= ~(1<<RELAY_2);
            for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
              Relay_[RELAY_2]->R[j].__Mode=__Mode_None;
              Memory_Relay_Set(RELAY_2, j, Relay_[RELAY_2]->R[j]);
            }
          }
          storage.NVS_SetUInt("RELAY", "RELAY_ENABLE", RELAY_ENABLE);
          server.send(200, "text/plain", response_ISTAR());
        }else if(DEVICE==OTHER){
          if(Relay_[RELAY_2]->R[0].__Mode==__Mode_Manual)
            Relay_Set_Defualt(DEVICE);
          String JSON = server.arg("JSON");
          JsonObject&  root = jsonBuffer.parseObject(JSON);
          TimeSchedule_Set[RELAY_2]  = root["NUM"].as<int>();
          Relay_[RELAY_2]->Number_Time_Schedule = root["NUM"].as<int>();
          String SLOT = getJsonVal(JSON, "SLOT");
          for(int j=0; j<TimeSchedule_Set[RELAY_2]; j++){
            String str_slot = root["SLOT"][j];
            JsonObject&  slot = jsonBuffer.parseObject(str_slot);
            Relay_[RELAY_2]->R[j].__Mode=(__Config_Mode_Enum)slot["TYPE"].as<int>();
            Relay_[RELAY_2]->R[j].Time_Schedule.timestamp_start = slot["TIMESTART"].as<int>();
            Relay_[RELAY_2]->R[j].Time_Schedule.duration = slot["DURATION"].as<int>();
            Relay_[RELAY_2]->R[j].Loop.time_on = slot["TIMEON"].as<int>();
            Relay_[RELAY_2]->R[j].Loop.time_off = slot["TIMEOFF"].as<int>();
            Memory_Relay_Set(RELAY_2, j, Relay_[RELAY_2]->R[j]);
          }
          char c[2] = {1 + 0x30, 0};
          storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, TimeSchedule_Set[RELAY_2]);
          server.send(200, "text/plain", response_OTHER());
        }

      }break;
      case 8:{  // rl3
        iStar_Params.Manual = 0;
        if(DEVICE==iSTAR_DEVICE){
          //String JSON = ;
          JsonObject&  root = jsonBuffer.parseObject(server.arg("JSON"));
          if(root["EN"].as<int>()==1){
            RELAY_ENABLE |= (1<<RELAY_3);
            iStarTemp[RELAY_3].T_ON = root["TON"].as<int>();
            iStarTemp[RELAY_3].T_OFF = root["TOFF"].as<int>();
            Memory_temperature_set();

            if(iStar_Params.R_CAP!=0){
              int HEATER_time_max = (int)(iStar_Params.TANK_VOL*1000*4.18*(abs(iStar_Params.TBS-TB)))/(iStar_Params.R_CAP);
              Serial.println("TIME HEATER->"+String(HEATER_time_max));
            }
            for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
              Relay_[RELAY_3]->R[j].__Mode=__Mode_Condition;
              Memory_Relay_Set(RELAY_3, j, Relay_[RELAY_3]->R[j]);
            }
          }
          else{
            RELAY_ENABLE &= ~(1<<RELAY_3);
            for(int j=0; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
              Relay_[RELAY_3]->R[j].__Mode=__Mode_None;
              Memory_Relay_Set(RELAY_3, j, Relay_[RELAY_3]->R[j]);
            }
          }
          storage.NVS_SetUInt("RELAY", "RELAY_ENABLE", RELAY_ENABLE);
          server.send(200, "text/plain", response_ISTAR());
        }else if(DEVICE==OTHER){
          if(Relay_[RELAY_3]->R[0].__Mode==__Mode_Manual)
            Relay_Set_Defualt(DEVICE);

          String JSON = server.arg("JSON");
          JsonObject&  root = jsonBuffer.parseObject(JSON);
          TimeSchedule_Set[RELAY_3]  = root["NUM"].as<int>();
          Relay_[RELAY_3]->Number_Time_Schedule = root["NUM"].as<int>();
          String SLOT = getJsonVal(JSON, "SLOT");
          for(int j=0; j<TimeSchedule_Set[RELAY_3]; j++){
            String str_slot = root["SLOT"][j];
            JsonObject&  slot = jsonBuffer.parseObject(str_slot);
            Relay_[RELAY_3]->R[j].__Mode=(__Config_Mode_Enum)slot["TYPE"].as<int>();
            Relay_[RELAY_3]->R[j].Time_Schedule.timestamp_start = slot["TIMESTART"].as<int>();
            Relay_[RELAY_3]->R[j].Time_Schedule.duration = slot["DURATION"].as<int>();
            Relay_[RELAY_3]->R[j].Loop.time_on = slot["TIMEON"].as<int>();
            Relay_[RELAY_3]->R[j].Loop.time_off = slot["TIMEOFF"].as<int>();
            Memory_Relay_Set(RELAY_3, j, Relay_[RELAY_3]->R[j]);
          }
          char c[2] = {2 + 0x30, 0};
          storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, TimeSchedule_Set[RELAY_3]);
          server.send(200, "text/plain", response_OTHER());
        }

      }break;
      case 9:{  // istar time schedule
        String JSON = server.arg("JSON");
        JsonObject&  root = jsonBuffer.parseObject(JSON);
        int num = root["NUM"].as<int>();
        for(int i=0; i< RELAY_SIZE; i++){
          // set eeprom
          char c[2] = {i + 0x30, 0};
          storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, num);
          TimeSchedule_Set[i]  = num;
          if(!(i==0 && Relay_[0]->R[0].__Mode==__Mode_Condition)){
            Relay_[i]->Number_Time_Schedule = num;
            for(int j=0; j<num; j++){
              String str_slot = root["SLOT"][j];
              JsonObject&  slot = jsonBuffer.parseObject(str_slot);
              Relay_[i]->R[j].Time_Schedule.timestamp_start = slot["TIMESTART"].as<int>();
              Relay_[i]->R[j].Time_Schedule.duration = slot["DURATION"].as<int>();
              Memory_Relay_Set(i, j, Relay_[i]->R[j]);
            }
            for(int j=num; j<MAXIMUM_NUMBER_TIME_SCHEDULE; j++){
              Relay_[i]->R[j].Time_Schedule.timestamp_start = 0;
              Relay_[i]->R[j].Time_Schedule.duration = 0;
              Memory_Relay_Set(i, j, Relay_[i]->R[j]);
            }
          }
         }
         // debug_istar_schedule();
        response="update";
        server.send(200, "text/plain", response);
      }break;
      case 10:{ // manual
        if(iStar_Params.Manual!=server.arg("MANUAL").toInt()) 
          Relay_Set_Defualt(DEVICE);
        iStar_Params.Manual = 1;

        server.arg("MANNUAL_RL1").toInt()?iStar_Params.p_Manual|=(1<<0):iStar_Params.p_Manual&=~(1<<0);
        server.arg("MANNUAL_RL2").toInt()?iStar_Params.p_Manual|=(1<<1):iStar_Params.p_Manual&=~(1<<1);
        server.arg("MANNUAL_RL3").toInt()?iStar_Params.p_Manual|=(1<<2):iStar_Params.p_Manual&=~(1<<2);
        for(int i=0; i<RELAY_SIZE; i++){
          Relay_[i]->Number_Time_Schedule = 1;
          Relay_[i]->R[0].__Mode=__Mode_Manual;
          if(iStar_Params.p_Manual&(1<<i))
            Relay_[i]->R[0].Manual_Control = true;
          else
            Relay_[i]->R[0].Manual_Control = false;
          Memory_Relay_Set(i, 0, Relay_[i]->R[0]);
          char c[2] = {i + 0x30, 0};
          storage.NVS_SetUInt("RL_SCHEDULE", (const char*)c, Relay_[i]->Number_Time_Schedule);
        }
        response="update";
        server.send(200, "text/plain", response);
        Memory_istar_set();
      }break;
      case 13:{ // change product
        DEVICE = (ISRAR_Device)(server.arg("PRODUCT").toInt()); 
        if(last_device!=DEVICE){
          Relay_Set_Defualt(DEVICE);
          last_device=DEVICE;
        }
        if(DEVICE==iSTAR_DEVICE)
          server.send(200, "text/plain", response_ISTAR());
        else if(DEVICE==OTHER)
          server.send(200, "text/plain", response_OTHER());
        storage.NVS_SetUInt("SYSTEM", "DEVICE", (int)DEVICE);
        response="update";
        server.send(200, "text/plain", response);
      }break;
      case 14:{ // send default response
        if(DEVICE==OTHER)
          server.send(200, "text/plain", response_OTHER());
        else{
          server.send(200, "text/plain", response_ISTAR());
        }
      }break;
      case 15:{ // serial number
        String SSNUMBER = server.arg("SERIAL"); 
        char tmp[SSNUMBER.length() + 1];
        memset(tmp, 0, sizeof(tmp));
        SSNUMBER.toCharArray(tmp, sizeof(tmp));
        SSNUMBER.toCharArray(SERIAL_NUMBER, sizeof(SERIAL_NUMBER));
        storage.NVS_SetString("SYSTEM", "SERIAL_NUMBER", tmp);
        response="update";
        server.send(200, "text/plain", response);
      }break;
      case 16:{ // rs485 slave
        MB_mode = Modbus_Slave;
        storage.NVS_SetUInt("RS485", "MODE", (int)MB_mode); 
        String RS585ID = server.arg("RS485ID");
        RS585ID.toCharArray(RS485_SLAVE_ID, sizeof(RS485_SLAVE_ID)); 

        storage.NVS_SetString("RS485", "RS485ID", RS485_SLAVE_ID);  // nvs rs485 id
        storage.NVS_SetUInt("RS485", "MODE", (int)MB_mode); // nvs mode
        response="update";
        server.send(200, "text/plain", response);
      }break;
      case 17:{ // rs485 master
        if(server.arg("delete").toInt()==0){  // add DEVICE 
          MB_mode = Modbus_Master;
          storage.NVS_SetUInt("RS485", "MODE", (int)MB_mode);
          for(int i=0; i<RS485_MAX_DEVICE; i++){
            if(RS485_LIST_DEVICE[i].id <= 0){
              RS485_LIST_DEVICE[i].id = server.arg("id").toInt(); 
              RS485_LIST_DEVICE[i].RS485_DEVICE = (RS485_DEVICE_)server.arg("device").toInt();   
              Memory_RS485_Set_List();
              response="update";
              server.send(200, "text/plain", response);
              break;
            }
          }
        }else{  //remove device
          for(int i=0; i<RS485_MAX_DEVICE; i++){
            if(server.arg("id").toInt() == RS485_LIST_DEVICE[i].id){  
              for(int j=i; j<RS485_MAX_DEVICE; j++){
                if((j+1)<RS485_MAX_DEVICE-1){
                  RS485_LIST_DEVICE[j] = RS485_LIST_DEVICE[j+1];
                }else{
                  RS485_LIST_DEVICE[j].id=0;
                  RS485_LIST_DEVICE[j].RS485_DEVICE=(RS485_DEVICE_)0;
                }
              }
              break;
            }
          }
        }
        debug_rs485_list();
        Memory_RS485_Set_List();
        server.send(200, "text/plain", "update");
      }break;
      case 18:{ // MQTT CA
        Serial.println("setting certificate");
        String rc = server.arg("ROOTCA") ;
        String cer = server.arg("CERTIFICATE") ;
        String priv = server.arg("PRIVATEKEY") ; 

        if(SPIFFS_writeFile("/ROOTCA.txt", rc)){
          rc = SPIFFS_readFile("/ROOTCA.txt");
          httpsClient.setCACert(rc.c_str());
         }
          if(SPIFFS_writeFile("/CERTIFICATE.txt", cer)){
          cer = SPIFFS_readFile("/CERTIFICATE.txt");
          httpsClient.setCertificate(cer.c_str());
         }
         if(SPIFFS_writeFile("/PRIVATEKEY.txt", priv)){
          priv = SPIFFS_readFile("/PRIVATEKEY.txt");
          httpsClient.setPrivateKey(priv.c_str());
         }

        response="update";
        server.send(200, "text/plain", response);
      }break;
      case 99:{
        currentuser = Non_USER;
        response = "LOGOUT";
        server.send(200, "text/plain", response);
      }break;
  }
} 

String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "gzip"; //application/x-gzip
  return "text/plain";
}

bool handleFileRead(String path){
  String contentType = getContentType(path);
  File file = SPIFFS.open(path, "r");
  size_t sent = server.streamFile(file, contentType);
  file.close();
  return true;
}

String create_socket_json(){
  String js="{\"TIME\":" + String(SYSTEM_TIME) + ",\"";
  js+="FIRMWARE\":\"" + String(FW_VERSION) + "\",\"";
  js+="PCF8563\":" + String(0) + ",\"";    //ext_rtc.getSecondInDay()  // test rtc sđs
  js+="TEST_MODE\":" + String(IS_DURING_TEST_MODE) + ",\"";
  js+="LIVE_TIME\":" + String(Live_time) + ",\"";
  js+="RESET_COUNT\":" + String(Reset_count) + ",\"";
  js+="WIFI_STATE\":" + String(WiFi.status()) + ",\"";
  js+="WIFI_SIGNAL\":" + String(toWiFiQuality(WiFi.RSSI())) + ",\"";
  js+="MQTT_STATE\":" + String(mqttClient.connected()) + ",\"";
  js+="ADC1\":" + String(f_ADC[0]) + ",\"";
  js+="ADC2\":" + String(f_ADC[1]) + " ,\"";
  js+="ADC3\":" + String(f_ADC[2]) + " ,\"";
  js+="RL1_LIVE\":" + String(Relay_[0]->Time_live_on) +" ,\"";
  js+="RL2_LIVE\":" + String(Relay_[1]->Time_live_on) +" ,\"";
  js+="RL3_LIVE\":" + String(Relay_[2]->Time_live_on) + "}";
  return js;
}
void debug_rs485_list(){
  for(int i=0; i<RS485_MAX_DEVICE; i++){
    if(RS485_LIST_DEVICE[i].id != 0){
      if(RS485_LIST_DEVICE[i].RS485_DEVICE==D_MFM)
        Serial.print("Đồng hồ MFM ");
      else if(RS485_LIST_DEVICE[i].RS485_DEVICE==D_DPM)
        Serial.print("Đồng hồ DPM");
      else if(RS485_LIST_DEVICE[i].RS485_DEVICE==InverterSolarbk)
        Serial.print("Inverter SolarBK ");
      Serial.println("id: "+String(RS485_LIST_DEVICE[i].id));
    }
  }
}