#include "RTC.h"


bool RTC::sync(long gmtOffset_sec, int daylightOffset_sec, const char *server1, const char *server2, const char *server3)
{
    configTime(gmtOffset_sec, daylightOffset_sec, server1, server2, server3);
    return check();
}

bool RTC::setTime(int h, int m, int s, int d, int M, int Y)
{
    struct tm tm = { 0 };
    tm.tm_hour = h;
    tm.tm_min = m;
    tm.tm_sec = s;
    tm.tm_mday = d;
    tm.tm_mon = M;
    if(Y >= 2000)
    {
        tm.tm_year = Y - 1900;
    }
    else
    {
        tm.tm_year = Y;
    }
    return setTime(tm);
}

bool RTC::setTime(tm tm)
{   
    time_t t = mktime(&tm);
    struct timeval now = {.tv_sec = t};
    Serial.println(String(tm.tm_hour)+":.."+String(tm.tm_min)+":.."+String(tm.tm_sec));
    Serial.println(String(tm.tm_mday)+"/.."+String(tm.tm_mon)+"/.."+String(tm.tm_year));
    settimeofday(&now, NULL);
    return check();
}

bool RTC::check()
{
    struct tm timeinfo;
    return check(&timeinfo);
}

bool RTC::check(tm *t)
{
    if (!getLocalTime(t))
    {
        log_e("RTC check fail.");
        return 0;
    }
    else
    {
        log_d("Time: %02d/%02d/%04d\t%02d:%02d:%02d.", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900, t->tm_hour, t->tm_min, t->tm_sec);
        return 1;
    }
}

int RTC::getSecondInDay()
{
    struct tm timeinfo;
    int s;
    if(getLocalTime(&timeinfo))
    {
        s = timeToSecond(timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        //log_d("Second:%d", s);
        return s;
    }
    else
    {
        log_e("RTC check fail.");
        return 0;
    }
    return 0;
}

int RTC::timeToSecond(int h, int m, int s)
{
    if(h >= 24 || m >= 60 || s >= 60)
    {
        return 0;
    }
    return (h * 3600) + (m * 60) + s;
}

uint32_t RTC::converToUnixTime(tm ti)
{
    uint32_t t;
    byte m, d, h, min, second;
    uint16_t y;
    y = ti.tm_year + 1900;
    // y+=2000;
    m = ti.tm_mon + 1;
    d = ti.tm_mday;
    h = ti.tm_hour;
    min = ti.tm_min;
    second = ti.tm_sec;
    //Serial.println(String(d)+"/."+String(m)+"/."+String(y));
    //Serial.println(String(h)+"/."+String(min)+"/."+String(second));
    if(m <= 2)
    {
        m += 12;
        y -= 1;
    }
    //Convert years to days
    t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
    //Convert months to days
    t += (30 * m) + (3 * (m + 1) / 5) + d;
    //Unix time starts on January 1st, 1970
    t -= 719561;
    //Convert days to seconds
    t *= 86400;
    //Add hours, minutes and seconds
    t += (3600 * h) + (60 * min) + second;

    //Return Unix time
    return t;
}

uint32_t RTC::converToUnixTime()
{
    struct tm timeinfo;
    if(getLocalTime(&timeinfo))
    {
        return converToUnixTime(timeinfo);
    }
    return 0;
}

tm RTC::get()
{
    struct tm timeinfo={0};
    if(getLocalTime(&timeinfo))
    {
        Serial.println("iternal rtc->"+String(timeinfo.tm_hour)+":"+String(timeinfo.tm_min)+":"+String(timeinfo.tm_sec));
        Serial.println("iternal rtc->"+String(timeinfo.tm_mday)+"/"+String(timeinfo.tm_mon)+"/"+String(timeinfo.tm_year));
        return timeinfo;
    }
    return timeinfo;

}