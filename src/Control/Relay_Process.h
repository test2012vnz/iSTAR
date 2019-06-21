#ifndef RELAY_PROCESS_H
#define RELAY_PROCESS_H

#include "Arduino.h"


#ifndef RELAY_SIZE
#define RELAY_SIZE  3
#endif

#ifndef MAXIMUM_NUMBER_TIME_SCHEDULE
#define MAXIMUM_NUMBER_TIME_SCHEDULE  5
#endif

typedef struct
{
    int timestamp_start;
    int duration;
} Time_Schedule_Structure;

typedef struct
{
    uint32_t *on_condition;
    uint32_t *off_condition;
    uint32_t *fail_condition;
    uint32_t *time_min;
    uint32_t *time_max;
    uint32_t *time_fail_reset;
    uint32_t *fail;
} Condition_Structure;

typedef struct
{
    int time_on;
    int time_off;
} Loop_Structure;

typedef enum
{
    __Mode_None = 0,
    __Mode_Condition,
    __Mode_Loop,
    __Mode_On_in_Time,
    __Mode_Manual
} __Config_Mode_Enum;

typedef struct
{
    int status;
    int timestamp;
} Timer_Control_Structure;

class __Config
{
protected:

public:
    void setMode(__Config_Mode_Enum m)
    {
        __Mode = m;
    }
    void setCondition(Condition_Structure c)
    {
        Condition = c;
    }
    void setLoop(Loop_Structure l)
    {
        Loop = l;
    }
    Time_Schedule_Structure Time_Schedule={};

    __Config_Mode_Enum __Mode={};

    Condition_Structure  Condition={};
    Loop_Structure  Loop={};
    __Config_Mode_Enum __Previous_Mode;
    bool Manual_Control;
};

class Relay_Basic: public __Config
{
public:
    Relay_Basic()
    {
        m_id = s_next++;
    }
    int relay_number;
    int run(int x, bool g_reset, bool without_time_max=false);

private:
    int m_id;
    static int s_next;
    Timer_Control_Structure ON;
    Timer_Control_Structure OFF;
    Timer_Control_Structure FAIL;
};

typedef struct 
{
    float *TTAM;
    float *TBON;
    float *THOI;
    int *TBONS;
}DEBUG_STRUCT;

class Relay
{
public:
    DEBUG_STRUCT DEBUG_STR;         //  FOR TEST
    bool g_reset = false;
    int relay_number = 0;              
    uint32_t Time_live_on=0;
    uint8_t Number_Time_Schedule = 0;
    Relay_Basic R[MAXIMUM_NUMBER_TIME_SCHEDULE];
    Relay(int pin)
    {
        p = pin;
        pinMode(pin, OUTPUT);
    }
    void run(int x)                       // custom
    {
        // Serial.println("Number_Time_Schedule->"+String(Number_Time_Schedule));
        if(Number_Time_Schedule== 0){    
            g_reset = true;
            digitalWrite(p, LOW);
        }
        state_waiting  =false;
        last_result = 0;
        for (int i = 0; i < Number_Time_Schedule; i++) {
            int result;
            if(relay_number != 3)
                result = R[i].run(x, g_reset);
            else 
                result = R[i].run(x, g_reset, true);
            if((i == Number_Time_Schedule -1) && g_reset==true)
            {
                Serial.println("---reset schedule complete---");
                g_reset = false;
            }

            if(result ==0){
                last_result |=0;
                state_waiting  = true;
            }
            else if(result==1){
                last_result |= 1;
            }
            else if(result==-1){   
                last_result |= 0;
            }
        }
        if(x==0)
            Time_live_on=0;
        if(last_result == 1){
            if(a!=last_result){             // debug
                String str = "RELAY "+String(relay_number)+"-->ON  | ";
                str+= "off_condition->"+String(*R[0].Condition.off_condition);
                str+= " fail_condition->"+String(*R[0].Condition.fail);
                if(relay_number==1){
                    str+= " TT->"+String((int)(*DEBUG_STR.TTAM))+" TB->"+String((int)(*DEBUG_STR.TBON));
                }else if(relay_number==2){
                    str+= " TB->"+String((int)(*DEBUG_STR.TBON))+" TH->"+String((int)(*DEBUG_STR.THOI));
                }else if(relay_number==3){
                    str+= " TB->"+String((int)(*DEBUG_STR.TBONS))+" TH->"+String((int)(*DEBUG_STR.THOI));
                }
                Serial.println(str);
            }
            Time_live_on+=1;
            a = last_result;
            digitalWrite(p, HIGH);
        }
        else{
            if(!state_waiting){
                if(a!=last_result){         // debugs

                    String str = "RELAY "+String(relay_number)+"-->OFF | ";
                    str+= "off_condition->"+String(*R[0].Condition.off_condition);
                    str+= " fail_condition->"+String(*R[0].Condition.fail);
                    if(relay_number==1){
                        str+= " TT->"+String((int)(*DEBUG_STR.TTAM))+" TB->"+String((int)(*DEBUG_STR.TBON));
                    }else if(relay_number==2){
                        str+= " TB->"+String((int)(*DEBUG_STR.TBON))+" TH->"+String((int)(*DEBUG_STR.THOI));
                    }else if(relay_number==3){
                        str+= " TBS->"+String((int)(*DEBUG_STR.TBONS))+" TH->"+String((int)(*DEBUG_STR.THOI));
                    }
                    Serial.println(str);
                }
                a = last_result;
                digitalWrite(p, LOW);
            }
        }
        vTaskDelay(1);
    }
private:
    int a = 0;                      // debugs
    int p;
    int last_result=0;
    bool state_waiting = false;
};

class Relay_Command
{
public:
    typedef void(Relay:: *Action)(int x);
    Relay_Command(Relay *object, Action method)
    {
        m_object = object;
        m_method = method;
    }
    void execute(int x)
    {
        (m_object->*m_method)(x);
    }
private:
    Relay *m_object;
    Action m_method;
};

template <typename T> class Relay_Control
{
public:
    Relay_Control()
    {
        m_add = m_remove = 0;
        number_of_item = 0;
    }
    void enque(T *c)
    {
        number_of_item++;
        m_array[number_of_item % SIZE] = c;
    }
    T *deque(int i)
    {
        int temp = i;
        //      m_remove = (m_remove + 1) % SIZE;/
        return m_array[temp];
    }

    void run(int x)
    {
        int c;
        if(number_of_item > SIZE)
        {
            c = SIZE;
        }
        for(int i = 0; i < c; i++)
        {
            m_array[i]->run(x);
        }
    }
    int number_of_item;
private:
    enum
    {
        SIZE = RELAY_SIZE
    };
    T *m_array[SIZE];
    int m_add, m_remove;
};

#endif
