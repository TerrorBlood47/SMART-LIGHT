
#include "RccConfig.h"
#include "Delay.h"
#include "UART2.h"
#include "PWM.h"
#include<stdbool.h>
#include<stdint.h>
#include <math.h>

#include <stdlib.h>
#include <string.h>

#include "UART3.h"


#define MAX_STRING_LENGTH 1024U



int get_PWM_value2(const char* string) {
    char* start_ptr = strchr(string, '{');
    if (start_ptr == NULL) {
        return 0; 
    }

    
    char* end_ptr = strchr(start_ptr, '}');
    if (end_ptr == NULL) {
        return 0; 
    }
   
    return atoi(start_ptr + 1);
}


int main (void)
{
	SysClockConfig ();
	TIM6Config();
	Uart2Config(); // for Terminal
	
	Uart4Config(); // for communicating with the bluetooth module
	
	PWM_init();
	
	Delay_ms(3000);
	
	
	UART2_SendString("Hello from UART2(TERMINAL)\r\n");
	
	
	while (1)
	{	
		char buf2[MAX_STRING_LENGTH];
		UART4_GetString(buf2, MAX_STRING_LENGTH);
		
		int pwm_value_in_percentage = get_PWM_value2(buf2);
		update_brightness_level(pwm_value_in_percentage);
		
		if(pwm_value_in_percentage==0){
			UART2_SendString("SOMETHING WRONG\r\n");
		}
		
		UART2_SendString(buf2);
		UART2_SendString("sent to terminal\r\n");
		
		UART4_SendString(buf2);

		Delay_ms(1000);
	
	}
	
}
