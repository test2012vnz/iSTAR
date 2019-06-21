#ifndef RTC_H
#define RTC_H
#include "Arduino.h"
#include <WiFi.h>
#include "time.h"

class RTC
{
public:
    bool sync(long gmtOffset_sec = 25200, int daylightOffset_sec = 0, const char *server1 = "asia.pool.ntp.org", const char *server2 = "pool.ntp.org", const char *server3 = "sg.pool.ntp.org");
    bool setTime(int h, int m, int s, int d, int M, int Y);
    bool setTime(tm tm);
    bool check();
    bool check(tm *);
    tm get();
    int getSecondInDay();
    int timeToSecond(int h, int m, int s);
    uint32_t converToUnixTime(tm t);
    uint32_t converToUnixTime();

private:

};

#endif