#include<stdint.h>
#include "stm32f446xx.h"
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void GPIO_Init(void);

void Power_ON();

void Power_OFF();

bool isPowerON();
	
int get_value2(const char* string);