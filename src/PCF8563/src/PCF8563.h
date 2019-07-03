

#ifndef PCF8563_H
#define PCF8563_H

#define RTCC_R      0xa3
#define RTCC_W      0xa2

#define RTCC_SEC        1
#define RTCC_MIN        2
#define RTCC_HR         3
#define RTCC_DAY        4
#define RTCC_WEEKDAY    5
#define RTCC_MONTH      6
#define RTCC_YEAR       7
#define RTCC_CENTURY    8

/* register addresses in the rtc */
#define RTCC_STAT1_ADDR     0x0
#define RTCC_STAT2_ADDR     0x01
#define RTCC_SEC_ADDR       0x02
#define RTCC_MIN_ADDR       0x03
#define RTCC_HR_ADDR        0x04
#define RTCC_DAY_ADDR       0x05
#define RTCC_WEEKDAY_ADDR   0x06
#define RTCC_MONTH_ADDR     0x07
#define RTCC_YEAR_ADDR      0x08
#define RTCC_ALRM_MIN_ADDR  0x09
#define RTCC_SQW_ADDR       0x0D
#define RTCC_TIMER1_ADDR    0x0E
#define RTCC_TIMER2_ADDR    0x0F

/* setting the alarm flag to 0 enables the alarm.
 * set it to 1 to disable the alarm for that value.
*/
#define RTCC_ALARM          0x80
#define RTCC_ALARM_AIE      0x02
#define RTCC_ALARM_AF       0x08
/* optional val for no alarm setting */
#define RTCC_NO_ALARM       99

#define RTCC_TIMER_TIE      0x01  // Timer Interrupt Enable

#define RTCC_TIMER_TF       0x04  // Timer Flag, read/write active state
                                  // When clearing, be sure to set RTCC_TIMER_AF
                                  // to 1 (see note above).
#define RTCC_TIMER_TI_TP    0x10  // 0: INT is active when TF is active
                                  //    (subject to the status of TIE)
                                  // 1: INT pulses active
                                  //    (subject to the status of TIE);
                                  // Note: TF stays active until cleared
                                  // no matter what RTCC_TIMER_TI_TP is.
#define RTCC_TIMER_TD10     0x03  // Timer source clock, TMR_1MIN saves power
#define RTCC_TIMER_TE       0x80  // Timer 1:enable/0:disable

/* Timer source-clock frequency constants */
#define TMR_4096HZ      B00000000
#define TMR_64Hz        B00000001
#define TMR_1Hz         B00000010
#define TMR_1MIN        B00000011

#define RTCC_CENTURY_MASK   0x80
#define RTCC_VLSEC_MASK     0x80

/* date format flags */
#define RTCC_DATE_WORLD     0x01
#define RTCC_DATE_ASIA      0x02
#define RTCC_DATE_US        0x04
/* time format flags */
#define RTCC_TIME_HMS       0x01
#define RTCC_TIME_HM        0x02

/* square wave contants */
#define SQW_DISABLE     B00000000
#define SQW_32KHZ       B10000000
#define SQW_1024HZ      B10000001
#define SQW_32HZ        B10000010
#define SQW_1HZ         B10000011

#include <Arduino.h>
#include <Wire.h>
#include "WiFi.h"
#include "time.h"

/* arduino class */
class PCF8563 {
    public:
    PCF8563(int sda, int scl);

    void zeroClock();           /* Zero date/time, alarm / timer, default clkout */
    void clearStatus();         /* set both status bytes to zero */
    byte readStatus1();
    void clearVoltLow(void);    /* Only clearing is possible */

    tm get();     /* get date and time vals to local vars */
    tm setTime(byte day, byte month, byte year, byte weekday,  byte hour, byte minute, byte sec);
    tm setTime(tm t);

    // Sets date/time to static fixed values, disable all alarms
    // use zeroClock() above to guarantee lowest possible values instead.
    void initClock();
    uint8_t read(uint8_t address);
    void write(uint8_t address, uint8_t data);
    // Slightly unsafe, don't use for new code, use above instead!
    void setTime(byte hour, byte minute, byte sec);
    void getTime();  // unsafe, don't use
    void setDate(byte day, byte weekday, byte month, byte year);
    void getDate();  // unsafe, don't use
    bool check();
    bool check(tm t);
    int getSecondInDay();
    private:
    /* methods */
    byte decToBcd(byte value);
    byte bcdToDec(byte value);
    /* time variables */
    byte hour;
    byte minute;
    bool volt_low;
    byte sec;
    byte day;
    byte weekday;
    byte month;
    byte year;
    /* support */
    byte status1;
    byte status2;
    bool century;

    char strOut[9];
    char strDate[11];

    int PCF8563_ADDR;

    struct tm DateTime;
};

#endif
