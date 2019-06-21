

#include <Arduino.h>
#include "PCF8563.h"

PCF8563::PCF8563(int sda, int scl)
{
    Wire.begin(sda, scl);
    PCF8563_ADDR = RTCC_R>>1;
}

byte PCF8563::decToBcd(byte val)
{
    return ( (val/10*16) + (val%10) );
}

byte PCF8563::bcdToDec(byte val)
{
    return ( (val/16*10) + (val%16) );
}

void PCF8563::zeroClock()
{
    vTaskDelay(10);
    Wire.beginTransmission(PCF8563_ADDR);    // Issue I2C start signal
    Wire.write((byte)0x0);        // start address

    Wire.write((byte)0x0);     //control/status1
    Wire.write((byte)0x0);     //control/status2
    Wire.write((byte)0x00);    //set seconds to 0 & VL to 0
    Wire.write((byte)0x00);    //set minutes to 0
    Wire.write((byte)0x00);    //set hour to 0
    Wire.write((byte)0x01);    //set day to 1
    Wire.write((byte)0x00);    //set weekday to 0
    Wire.write((byte)0x81);    //set month to 1, century to 1900
    Wire.write((byte)0x00);    //set year to 0
    Wire.write((byte)0x80);    //minute alarm value reset to 00
    Wire.write((byte)0x80);    //hour alarm value reset to 00
    Wire.write((byte)0x80);    //day alarm value reset to 00
    Wire.write((byte)0x80);    //weekday alarm value reset to 00
    Wire.write((byte)SQW_32KHZ); //set SQW to default, see: setSquareWave
    Wire.write((byte)0x0);     //timer off
    Wire.endTransmission();
}

void PCF8563::clearStatus()
{
    Wire.beginTransmission(PCF8563_ADDR);    // Issue I2C start signal
    Wire.write((byte)0x0);
    Wire.write((byte)0x0);                 //control/status1
    Wire.write((byte)0x0);                 //control/status2
    Wire.endTransmission();
}

tm PCF8563::get(void){
    Wire.beginTransmission(PCF8563_ADDR);
    Wire.write((byte)RTCC_STAT1_ADDR);
    Wire.endTransmission();
    /* As per data sheet, have to read everything all in one operation */
    uint8_t readBuffer[16] = {0};
    Wire.requestFrom(PCF8563_ADDR,  16);
    for (int  i=0; i < 16; i++)
        readBuffer[i] = Wire.read();

    // status bytes
    status1 = readBuffer[0];
    status2 = readBuffer[1];

    volt_low = readBuffer[2] & RTCC_VLSEC_MASK;  //VL_Seconds
    DateTime.tm_sec = bcdToDec(readBuffer[2] & ~RTCC_VLSEC_MASK);
    DateTime.tm_min = bcdToDec(readBuffer[3] & 0x7f);
    //0x3f = 0b00111111
    DateTime.tm_hour = bcdToDec(readBuffer[4] & 0x3f);

    // date bytes
    //0x3f = 0b00111111
    DateTime.tm_mday = bcdToDec(readBuffer[5] & 0x3f);
    //0x07 = 0b00000111
    DateTime.tm_wday = bcdToDec(readBuffer[6] & 0x07);
    //get raw month data byte and set month and century with it.
    DateTime.tm_mon = bcdToDec(readBuffer[7] & 0x1f) -1;
    DateTime.tm_year = bcdToDec(readBuffer[8])+100;

    return DateTime;
}

tm PCF8563::setTime(byte day, byte month, byte year, byte weekday,  byte hour, byte minute, byte sec){
    /* year val is 00 to 99, xx
        with the highest bit of month = century
        0=20xx
        1=19xx
        */
    // initClock();
    month = decToBcd(month);
    month &= ~RTCC_CENTURY_MASK;
    /* As per data sheet, have to set everything all in one operation */
    Wire.beginTransmission(PCF8563_ADDR);    // Issue I2C start signal
    Wire.write(RTCC_SEC_ADDR);       // send addr low byte, req'd
    Wire.write(decToBcd(sec) &~RTCC_VLSEC_MASK); //set sec, clear VL bit
    Wire.write(decToBcd(minute));    //set minutes
    Wire.write(decToBcd(hour));        //set hour
    Wire.write(decToBcd(day));            //set day
    Wire.write(decToBcd(weekday));    //set weekday
    Wire.write(month);                 //set month, century to 1
    Wire.write(decToBcd(year));        //set year to 99
    Wire.endTransmission();
    // Keep values in-sync with device
    vTaskDelay(50);
     return get();
}

tm PCF8563::setTime(tm t){
    return setTime((byte)t.tm_mday, (byte)(t.tm_mon + 1), (byte)(t.tm_year%100), (byte)t.tm_wday, (byte)t.tm_hour, (byte)t.tm_min, (byte)t.tm_sec);
}

void PCF8563::initClock(){
    Wire.beginTransmission(PCF8563_ADDR);    // Issue I2C start signal
    Wire.write((byte)0x0);        // start address

    Wire.write((byte)0x0);     //control/status1
    Wire.write((byte)0x0);     //control/status2
    Wire.write((byte)0x81);     //set seconds & VL
    Wire.write((byte)0x01);    //set minutes
    Wire.write((byte)0x01);    //set hour
    Wire.write((byte)0x01);    //set day
    Wire.write((byte)0x01);    //set weekday
    Wire.write((byte)0x01);     //set month, century to 1
    Wire.write((byte)0x01);    //set year to 99
    Wire.write((byte)0x80);    //minute alarm value reset to 00
    Wire.write((byte)0x80);    //hour alarm value reset to 00
    Wire.write((byte)0x80);    //day alarm value reset to 00
    Wire.write((byte)0x80);    //weekday alarm value reset to 00
    Wire.write((byte)0x0);     //set SQW, see: setSquareWave
    Wire.write((byte)0x0);     //timer off
    Wire.endTransmission();
}
bool PCF8563::check(){
    return check(get());
}

bool PCF8563::check(tm t){
    Serial.println("ext rtc->"+String(DateTime.tm_hour)+":"+String(DateTime.tm_min)+":"+String(DateTime.tm_sec));
    Serial.println("ext rtc->"+String(DateTime.tm_mday)+"/"+String(DateTime.tm_mon)+"/"+String(DateTime.tm_year));
    if(DateTime.tm_hour>=24|| DateTime.tm_min>=60)
        return false;
    if(DateTime.tm_year + 100 > (2016 - 1900))
    {
        return true;
    }
    return false;
}

int PCF8563::getSecondInDay(){
    if(check())
        return DateTime.tm_hour*3600+DateTime.tm_min*60+DateTime.tm_sec;
    return 0;
}