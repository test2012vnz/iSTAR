#include "NVS_ESP32.h"
NVS_EPPROM storage;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  char Name[20];
  storage.NVS_GetString("Storage","Name",Name,20);
  Serial.printf("Name: %s\n", Name);
  storage.NVS_SetString("Storage","Name","phaphh");
  Serial.println("Restarting in 10 seconds...");
  delay(10000);

  // Restart ESP
  ESP.restart();
}

void loop() {
  // put your main code here, to run repeatedly:

}
