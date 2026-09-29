#include "UART2.h"


void Uart4Config (void)
{
		/******* STEPS FOLLOWED ********
	
	1. Enable the UART CLOCK and GPIO CLOCK
	2. Configure the UART PINs for ALternate Functions
	3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	4. Program the M bit in USART_CR1 to define the word length.
	5. Select the desired baud rate using the USART_BRR register.
	6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register

	********************************/
	
	// 1. Enable the UART CLOCK and GPIO CLOCK
	RCC->APB1ENR |= RCC_APB1ENR_UART4EN;  // Enable UART4 CLOCK
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA CLOCK
	
	// 2. Configure the UART PINs for ALternate Functions
	
	GPIOA->MODER |= (2<<0);  // Bits (1:0)= 1:0 --> Alternate Function for Pin PA0
	GPIOA->MODER |= (2<<2);  // Bits (3:2)= 1:0 --> Alternate Function for Pin PA1
	
	GPIOA->OSPEEDR |= (3<<0) | (3<<1);  // Bits (1:0)= 1:1 and Bits (3:2)= 1:1 --> High Speed for PIN PA0 and PA1
	
	GPIOA->AFR[0] |= (8<<0);  // Bytes (3:2:1:0) = 1:0:0:0  --> AF8 Alternate function for UART4 at Pin PA0
	GPIOA->AFR[0] |= (8<<4); // Bytes (7:6:5:4) = 1:0:0:0  --> AF8 Alternate function for UART4 at Pin PA1
	
	// 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	UART4->CR1 = 0x00;  // clear all
	UART4->CR1 |= (1<<13);  // UE = 1... Enable USART
	
	// 4. Program the M bit in USART_CR1 to define the word length.
	UART4->CR1 &= ~(1<<12);  // M =0; 8 bit word length
	
	// 5. Select the desired baud rate using the USART_BRR register.
	//UART4->BRR = (4U<<0) | (73U<<4);   // Baud rate of 38400, PCLK1 at 45MHz
	//UART4->BRR = (7U<<0) | (24U<<4);   // Baud rate of 115200, PCLK1 at 45MHz
	UART4->BRR = (0U<<0) | (293U<<4);   // Baud rate of 9600, PCLK1 at 45MHz
	
	
	// 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
	UART4->CR1 |= (1<<2); // RE=1.. Enable the Receiver
	UART4->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
}





void UART4_SendChar (uint8_t c)
{
		/*********** STEPS FOLLOWED *************
	
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	
	****************************************/
	
	UART4->DR = c; // load the data into DR register
	while (!(UART4->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}
	


void UART4_SendString (char *string)
{
	while (*string) UART4_SendChar (*string++);
}



uint8_t UART4_GetChar (void)
{
			/*********** STEPS FOLLOWED *************
	
	1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	2. Read the data from USART_DR  Register. This also clears the RXNE bit
	
	****************************************/

	uint8_t temp;
	
	while (!(UART4->SR & (1<<5)));  // wait for RXNE bit to set
	temp = UART4->DR;  // Read the data. This clears the RXNE also
	return temp;
}


	
void UART4_GetString(char* buffer, int max_len)
{
		
		int i = 0;
	while(47)
	{		
			char c = (char) UART4_GetChar();
			buffer[i] = c;
			i++;
			
			if(c == '\n')
				{
					buffer[i] = '\0';
					break;
				}
			if (i >= max_len - 1)
    {
        buffer[max_len - 1] = '\0';
			break;
    }
	}
	
}


