#include "PWM.h"
#include "UART2.h"


void PWM_init(void){
		// Enable Clocks
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	
		//GPIO Config
		GPIOA->MODER &= ~(3U << (7*2));
		GPIOA->MODER |= (2U << (7*2)); //alternate fucntion for PA7
		
		GPIOA->AFR[0] &= ~(0xFU << (7*4)); 
		GPIOA->AFR[0] |= (0x2U << (7*4)); //CONNECT PA7 to AF1 (TIM3)
	
		// TIM2 Config
		TIM3->PSC = 90-1; //1 MHz clock
		TIM3->ARR = MAX_BRIGHTNESS_LEVEL-1;
	
		TIM3->CCR2 = 500; // 500/1000 = 50% brightness
	
		// This moves PSC, ARR, and CCR2 into the active hardware logic immediately.
    TIM3->EGR |= TIM_EGR_UG;
	
		TIM3->CCMR1 |= (6u << (TIM_CCMR1_OC2M_Pos)) | TIM_CCMR1_OC2PE; 
	
		TIM3->CCER |= TIM_CCER_CC2E;
	
		TIM3->CR1 |= TIM_CR1_CEN;
	
}

void update_brightness_level(int percentage){
	int value = (int)(((double)((double)percentage/100))*((double)MAX_BRIGHTNESS_LEVEL));
	
	/*
	if(value==0){
		UART2_SendString("Something wrong here");
	}
	*/
	
	TIM3->CCR2 = value; // value/1000 % brightness

}

