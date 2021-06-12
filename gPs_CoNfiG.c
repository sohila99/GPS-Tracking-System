#include "tm4c123gh6pm_registers.h"
#include "stdint.h"


void GPS_Init(void)
{
	SYSCTL_RCGCUART_R |= 0x04;
	SYSCTL_RCGCGPIO_R |= 0x04;
	
	UART1_CTL_R &= ~0x00000001; 
	UART1_IBRD_R = 104;
	UART1_FBRD_R = 11;
	UART1_LCRH_R = 0x70;
	UART1_CTL_R = 0x301;

	GPIO_PORTC_AFSEL_R |= 0x30;
	GPIO_PORTC_PCTL_R &= 0xFF00FFFF;
	GPIO_PORTC_PCTL_R |= 0x00220000;
	GPIO_PORTC_DEN_R |= 0x30;
}

uint8_t GPS_Data_Available(void)
{
	return ((UART1_FR_R & 0x00000010) == 0x00000010) ? 0 : 1;
}

uint8_t GPS_Receive(void)
{
	while (UART1_Available() != 1);
	return (uint8_t)(UART1_DR_R & 0xFF);
}
