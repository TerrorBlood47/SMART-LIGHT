#include <stdint.h>
#include "stm32f446xx.h"




//UART2 will be used as terminal com

void Uart2Config (void);

void UART2_SendChar (uint8_t c);
uint8_t UART2_GetChar (void);

void UART2_SendString (char *string);
void UART2_GetString(char* buffer, int max_len);

