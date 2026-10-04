#include<stdint.h>
#include "stm32f446xx.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BRIGHTNESS_LEVEL 1000U

void PWM_init(void);

void update_brightness_level(int percentage);

int get_PWM_value2(const char* string);

