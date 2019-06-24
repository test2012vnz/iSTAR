#ifndef INCLUDE_H
#define INCLUDE_H

#include <WiFiClientSecure.h>
#include <WebSocketsServer.h>
#include <WebServer.h>
#include <Update.h>
#include <SPIFFS.h>
#include <EEPROM.h>
// #include <WebSocketsClient.h>

// #include <AWS_IOT.h>
#include <ArduinoJson.h>
#include "json_device.h"
#include "src/wifi/src/wifi.h"
#include "src/Control/Relay_Process.h"
#include "src/NVS_ESP32/NVS_ESP32.h"
#include "src/PCF8563/src/PCF8563.h"
#include "src/dropbox/src/dropbox.h"
#include "src/RTC/src/RTC.h"
#include <PubSubClient.h>
// #include "src/proto/iStar.h"
// #include "src/proto/src/protobuf.h"
#include "src/rs485/src/rs485.h"
#include "Hardware_Pinout.h"
#include "Webserver.h"

#define RELAY_1   0
#define RELAY_2   1
#define RELAY_3   2
#define RS485_MAX_DEVICE  20

DynamicJsonBuffer jsonBuffer;
typedef enum {
  Non_USER = 0,
  Manu_USER,
  Installer_USER
} USER;
USER currentuser = Non_USER;

/*****************SYSTEM******************/
uint32_t SYSTEM_TIME;
char FW_VERSION[64] = "iSTAR-v20191706"; 
char SERIAL_NUMBER[64] = "0000-0000-000";
uint32_t FAIL_STATUS = 0;
uint32_t Reset_count;
uint32_t Live_time;
bool IS_DURING_TEST_MODE = false;

/*****************************************/
/*****************CONNECT*****************/
String iStar_pkg="";  // packet collection

bool RS485_pkg_ready = false;
_Wifi wifi_(&WiFi);
char cssid[64];
char cpass[64];
bool IS_WIFI_SETTING=false;
bool IS_WIFI_SCANNING = false;
bool IS_STA_NO_AP = false;

const char endpoint[] = "a2lv3cywt6s2d5-ats.iot.ap-northeast-1.amazonaws.com";
const int port = 8883;

// AWS_IOT *aws = new AWS_IOT;
char HOST_ADDRESS[]="a2lv3cywt6s2d5-ats.iot.ap-northeast-1.amazonaws.com";
char CLIENT_ID[]= "RD-TEST";
char pubTopic[] = "data/iStar";
char subTopic[] = "$aws/things/iStar/shadow/update/delta";
char rootca[2048];
char certificate[2048];
char private_key[2048];

dropbox box;          // dropbox ota


WiFiClientSecure httpsClient;
PubSubClient mqttClient(httpsClient);

WebSocketsServer webSocket = WebSocketsServer(81);
WebServer server(80);
File fsUploadFile;

/*****************************************/
/******************RS485******************/
typedef enum{
  Modbus_Null=0,
  Modbus_Master,
  Modbus_Slave
}Modbus_Mode_;
Modbus_Mode_ MB_mode=Modbus_Master;

char RS485_SLAVE_ID[16] = "00";
ModbusRTUSlave MB_SLAVE(1, &rs485);

typedef enum 
{
  D_MFM=0,
  D_DPM,
  InverterSolarbk
}RS485_DEVICE_;
typedef struct 
{
  int id;
  RS485_DEVICE_ RS485_DEVICE;

}RS485_LIST_DEVICE_;
RS485_LIST_DEVICE_ RS485_LIST_DEVICE[RS485_MAX_DEVICE];

/*****************************************/
/*******************RTC*******************/
#define RTC_OUTRANGE  (300)
PCF8563 ext_rtc(RTC_SDA,RTC_SCL);
RTC rtc;

/*****************************************/
/****************CONTROL******************/
Relay_Control <Relay> Relay_Control_;
Relay_Command *Relay_Command_[RELAY_SIZE];
Relay *Relay_[RELAY_SIZE];

/*****************************************/
/*****************ISTAR*******************/
typedef struct
{
  bool Manual = 0;
  uint8_t p_Manual = 0;
  int TBS = 60;
  int TTMAX = 80;
  int TBMAX =80;
  int R_CAP = 0;
  int TANK_VOL = 1;
}iStar_Parameters;
iStar_Parameters iStar_Params;

typedef enum
{
  DEVICE_NONE=0,
  iSTAR_DEVICE,
  OTHER
}ISRAR_Device;
ISRAR_Device DEVICE = DEVICE_NONE;
ISRAR_Device last_device = DEVICE_NONE;

typedef enum{
  iCON_Null=0,
  iCON_Wifi_Fail,
  iCON_MQTT_Fail,
  iCON_OK

}iCON_Status;
iCON_Status CON_Status;

typedef enum{
  iRUN_Null=0,
  iRUN_OK,
  iRUN_FAIL
}iRUN_Status;
iRUN_Status RUN_Status;

typedef struct{
  uint32_t on_condition;
  uint32_t off_condition;
  uint32_t fail_condition;
  uint32_t fail;
  uint32_t time_max = 300;
  uint32_t time_min=30;
  uint32_t time_fail_reset = 60;
}iStar_Condition;
iStar_Condition iStarMode[RELAY_SIZE];

typedef struct{
  int T_ON;
  int T_OFF;
}iStar_Temperature_Structure;
iStar_Temperature_Structure iStarTemp[RELAY_SIZE];

#define TB_SET        (iStar_Params.TBS)
#define TT_MAX        (iStar_Params.TTMAX)
#define TB_MAX        (iStar_Params.TBMAX)
#define TCF  20
#define TRF  20

#define TT_ON         (iStarTemp[0].T_ON)
#define TT_OFF        (iStarTemp[0].T_OFF)
#define TB_ON         (iStarTemp[1].T_ON)
#define TB_OFF        (iStarTemp[1].T_OFF)
#define TH_ON         (iStarTemp[2].T_ON)
#define TH_OFF        (iStarTemp[2].T_OFF)

uint8_t RELAY_ENABLE = 0;
uint32_t TimeSchedule_Set[RELAY_SIZE];
uint32_t *Relay_Time_on[3]={};

/*****************************************/
/*****************PROTO*******************/
// proto proto;
// Frame F = Frame_init_default;
// Frame O = Frame_init_default;
// iSTAR IstarProto;

/*****************************************/
/*****************EEPTOM******************/
#define EPPROM_SIZE 0x10000
NVS_EPPROM storage;
bool IS_EPPROM_OK = false;

/*****************************************/
/*****************TIMER*******************/
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer();

/*****************************************/
int HEATER_TIME_MAX_RUN = 0;
int HEATER_START_TIME = 0;


/* Partition:
  # Name,   Type, SubType, Offset,  Size, Flags
  nvs,      data, nvs,     0x9000,  0x3000,
  phy_init, data, phy,     0xc000,  0x2000,
  otadata,  data, ota,     0xe000,  0x2000,
  app0,     app,  ota_0,   0x10000, 0x140000,
  app1,     app,  ota_1,   0x150000,0x140000,
  eeprom,   data, 0x99,    0x290000,0x10000,
  spiffs,   data, spiffs,  0x2A0000,0x160000,
*/

#endif
