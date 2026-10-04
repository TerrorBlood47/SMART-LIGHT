
#include "RccConfig.h"
#include "Delay.h"
#include "UART2.h"
#include "PWM.h"
#include "Switch.h"
#include<stdbool.h>
#include<stdint.h>
#include <math.h>

#include <stdlib.h>
#include <string.h>

#include "UART3.h"


#define MAX_STRING_LENGTH 1024U


int main (void)
{
	SysClockConfig ();
	TIM6Config();
	Uart2Config(); // for Terminal
	
	Uart4Config(); // for communicating with the bluetooth module
	
	//PWM_init();
	
	GPIO_Init();
	
	Delay_ms(3000);
	
	
	UART2_SendString("Hello from UART2(TERMINAL)\r\n");
	
	
	/*
	while(47){
		
		Power_OFF();
		Delay_ms(5000);
		
		Power_ON();
		Delay_ms(5000);    
	}
	*/
	
	
	while (47)
	{	
		char buf2[MAX_STRING_LENGTH];
		UART4_GetString(buf2, MAX_STRING_LENGTH);
		UART2_SendString("HI\r\n");
		//UART2_SendString(buf2);
		
		
		int value = get_value2(buf2);

		if(value == 1){	//Power_OFF already
			Power_ON();
		}
		else{
			Power_OFF();
		}
		
		UART2_SendString(buf2);
		UART2_SendString("sent to terminal\r\n");
		
		//UART4_SendString(buf2);
		
		
		Delay_ms(500);
	
	}

	
}
