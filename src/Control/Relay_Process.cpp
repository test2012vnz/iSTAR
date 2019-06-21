#include "Relay_Process.h"


int Relay_Basic::s_next = 0;
//int Relay_Control::number_of_item=0;/

int Relay_Basic::run(int x, bool g_reset, bool without_time_max) {
  vTaskDelay(1);
  if (__Mode == __Mode_Manual) {
    if (Manual_Control == true) {
      return 1;
    } else {
      return -1;
    }
  }
  if((Time_Schedule.timestamp_start + Time_Schedule.duration) > 86400)
  {
      int timestamp_stop = Time_Schedule.timestamp_start + Time_Schedule.duration - 86400;
      if((x < timestamp_stop) || (x > Time_Schedule.timestamp_start))
      {
        
      }
      else
      {
          return -1;
      }
  }
  else  if ((x < Time_Schedule.timestamp_start) || (x > (Time_Schedule.timestamp_start + Time_Schedule.duration)))
  {
      // log_d("Out_range");
      OFF = {0, x};
      FAIL = {0,x};
      ON = {1, x};
      return -1;
  }

  if (__Mode != __Previous_Mode || g_reset) {
    __Previous_Mode = __Mode;
    if (__Previous_Mode == __Mode_Condition) {
      *Condition.fail = 0;
    }
    OFF = {0, x};
    FAIL = {0, x};
    ON = {0, x};
  }
  switch (__Mode) {
    case __Mode_None: {
        return -1;
      } break;
    case __Mode_Condition: {
      // Serial.println("--Mode Condition: x->"+String(x)+" ON.status->"+String(ON.status)
      //                 +" ON.timestamp->"+String(ON.timestamp));
       // Serial.println("RELAY["+String(relay_number)+"] on_condition->"+String(*Condition.on_condition)+" off_condition->"+String(*Condition.off_condition)
       //  +" fail_condition->"+String(*Condition.fail_condition)+"fail->"+String(*Condition.fail));
        if (FAIL.status) {
          // Serial.println("fail staus on");
          if ((x - FAIL.timestamp) > *Condition.time_fail_reset) {
            FAIL.status = 0;
            if (Condition.fail != NULL)  {
              *Condition.fail = 0;
            }
          }
        } else {
          if (*Condition.fail_condition) {
            if (Condition.fail != NULL)  {
              *Condition.fail = 2;
            }
TYPE1_ERROR:
            FAIL.timestamp = x ;
            FAIL.status = 1;
            ON.status = 0;
            return -1;
          } else if (ON.status == 1) {
            if (((x - ON.timestamp) > *Condition.time_max)&&(!without_time_max)) {
              vTaskDelay(1);
              // Serial.println("fail over time");
              if (Condition.fail != NULL)  {
                *Condition.fail = 1;
              }
              goto TYPE1_ERROR;
            }
            else if ((*Condition.off_condition) && ((x - ON.timestamp) > *Condition.time_min)) {
              // Serial.println("--OFF--");
              ON.status = 0;
              return -1;
            }
          }
          else if (*Condition.on_condition) {
            // Serial.println("--ON--");
            ON.status = 1;
            ON.timestamp = x;
            return 1;
          }
        }
        return 0;
      } break;
    case __Mode_Loop: {
        int deltax = abs((x - ON.timestamp)) % (Loop.time_on + Loop.time_off); // modify timstap
        if (deltax <= Loop.time_on) {
          // Serial.println("--MODE LOOP --> ON -- TIME: " +String(x)+" deltax: "+ String(deltax) + " timestamp: "+String(ON.timestamp));
          return 1;
        } else {
          // Serial.println("--MODE LOOP --> OFF -- TIME: " +String(x)+" deltax: "+ String(deltax) + " timestamp: "+String(ON.timestamp));
          return -1;
        }
      } break;
    case __Mode_On_in_Time: {
        return 1;
      } break;
  }
  return 0;
}

