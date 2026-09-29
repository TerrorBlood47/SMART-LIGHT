#include <stdint.h>
#include "stm32f446xx.h"




//UART2 will be used as terminal com


void Uart4Config(void);


void UART4_SendChar (uint8_t c);
void UART4_SendString (char *string);
uint8_t UART4_GetChar (void);
void UART4_GetString(char* buffer, int max_len);

