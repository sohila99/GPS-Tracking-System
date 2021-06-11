#include "tm4c123gh6pm_registers.h"
#include "stdint.h"


void GPS_Init(void)
{
	SYSCTL_RCGCUART_R |= 0x04;
	SYSCTL_RCGCGPIO_R |= 0x04;
	
	UART0_CTL_R &= ~
	
	
	
	



	GPIO_PORTC_AFSEL_R |= 0x30;
	GPIO_PORTC_PCTL_R &= 0xFF00FFFF;
	GPIO_PORTC_PCTL_R |= 0x00220000;
	GPIO_PORTC_DEN_R |= 0x30;


}
