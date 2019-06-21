#ifndef HARDWARE_PINOUT_H
#define HARDWARE_PINOUT_H

/* */
#define RTC_SDA       19	//18
#define RTC_SCL       21	//23

#define PIN_RELAY_1   25
#define PIN_RELAY_2   27
#define PIN_RELAY_3   4

#define CON_LED       33
#define RUN_LED       32
#define SPEAKER		  11

#define PIN_WTD       22

int Relay_PINOUT[RELAY_SIZE]={25,27,4};
rs485 rs485(TD501D485H,1,5,18);
#define ADC_SIZE  3
int ADC_PINTOUT[ADC_SIZE]={35,34,39};
float f_ADC[ADC_SIZE];

typedef enum{
	ERR_NULL = 		0,
	TT_ERROR = 		1,
	TB_ERROR = 		2,
	TH_ERROR = 		3,
	IN_RTC_ERROR = 	4,
	EXT_RTC_ERROR =	5,
	RL1_OVER_TIME = 6,
	RL1_FAIL_CON = 	7,
	RL2_OVER_TIME = 8,
	RL2_FAIL_CON = 	9,
	RL3_OVER_TIME = 10,
	RL3_FAIL_CON = 	11

} Error_List_Enum;

typedef class {
	Error_List_Enum err[16] = {};
	char time[16][10] = {};
	String toString(){
		String err_str = "";
		for(int i=0; i<16; i++){
			if(err[i!=0])
				err_str+=String(err[i])+" ";
		}
		return err_str;
	};
} Error_List;


#define TT  (f_ADC[0])
#define TB  (f_ADC[1])
#define TH  (f_ADC[2])

#define MAX_TEMP  120
#define MIN_TEMP  0

#define TT_ERROR 		(1<<0)	//
#define TB_ERROR 		(1<<1)	//
#define TH_ERROR 		(1<<2)	//

#define IN_RTC_ERROR 	(1<<3)
#define EXT_RTC_ERROR 	(1<<4)

#define RL1_OVER_TIME	(1<<5)
#define RL1_FAIL_CON	(1<<6)
#define RL2_OVER_TIME	(1<<7)
#define RL2_FAIL_CON	(1<<8)
#define RL3_OVER_TIME	(1<<9)
#define RL3_FAIL_CON	(1<<10)


#define WIFI_ERROR		(1<<11)
#define RS485_ERROR		(1<<12)

#endif
