#include "Switch.h"

void GPIO_Init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	//GPIO Config
	GPIOA->MODER &= ~(3U << (8*2));
	GPIOA->MODER |= (1U << (8*2)); //general purpose I/O for PA8

	GPIOA->OTYPER &= ~(1U <<8); //push-pull: to actively pull the signal HIGH or LOW
	//GPIOA->OTYPER |= (1U <<5); //open-drain: only pull to low LOW
	GPIOA -> OSPEEDR &= ~(3U << (8*2)); // low speed

}

void Power_ON(){
	GPIOA->BSRR = GPIO_BSRR_BS8; // BS=Bit Set, turning ON the pin means turning the bulb ON
}

void Power_OFF(){
		GPIOA->BSRR = GPIO_BSRR_BR8; 
}

bool isPowerON(){
		return ((GPIOA->ODR & (1<<8)) != 0);
}


int get_value2(const char* string) {
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


