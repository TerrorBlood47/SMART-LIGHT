#include<stdint.h>
#include "stm32f446xx.h"

#define MAX_BRIGHTNESS_LEVEL 1000U

void PWM_init(void);

void update_brightness_level(int percentage);

