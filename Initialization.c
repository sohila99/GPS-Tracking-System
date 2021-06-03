#include <stdio.h>
#include "C:\Users\naglaa\Desktop\ASU\2nd ECE\2nd Term\Embedded Systems\Embedded Project\tm4c123gh6pm.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define PF4                     (*((volatile unsigned long *)0x40025040))
#define PF3                     (*((volatile unsigned long *)0x40025020))
#define PF2                     (*((volatile unsigned long *)0x40025010))
#define PF1                     (*((volatile unsigned long *)0x40025008))
#define PF0                     (*((volatile unsigned long *)0x40025004))
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
#define PF123_mask             0x0E
#define PF04_mask               0x11
#define PF_mask                0x20

void SystemInit(){}
void RGBLED_Init ()
{
SYSCTL_RCGCGPIO_R |= 0x2F;
while ((SYSCTL_PRGPIO_R&0x2F) == 0){};
	
GPIO_PORTA_LOCK_R = 0x4C4F434B;
GPIO_PORTB_LOCK_R = 0x4C4F434B;
GPIO_PORTC_LOCK_R = 0x4C4F434B;
GPIO_PORTD_LOCK_R = 0x4C4F434B;
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTA_CR_R |= 0x1C;
GPIO_PORTB_CR_R |= 0x48;
GPIO_PORTC_CR_R |= 0xF0;
GPIO_PORTD_CR_R |= 0xC0;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTA_DIR_R |= 0x1C;
GPIO_PORTB_DIR_R |= 0x48;
GPIO_PORTC_DIR_R |= 0xF0;
GPIO_PORTD_DIR_R |= 0xC0;
GPIO_PORTF_DIR_R |= 0x0E;
GPIO_PORTA_DEN_R |= 0x1C;
GPIO_PORTB_DEN_R |= 0x48;
GPIO_PORTC_DEN_R |= 0xF0;
GPIO_PORTD_DEN_R |= 0xC0;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTA_AMSEL_R &= ~0x1C;
GPIO_PORTB_AMSEL_R &= ~0x48;
GPIO_PORTC_AMSEL_R &= ~0xF0;
GPIO_PORTD_AMSEL_R &= ~0xC0;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTA_AFSEL_R &= ~0x1C;
GPIO_PORTB_AFSEL_R &= ~0x48;
GPIO_PORTC_AFSEL_R &= ~0xF0;
GPIO_PORTD_AFSEL_R &= ~0xC0;
GPIO_PORTF_AFSEL_R &= ~0x0E;
GPIO_PORTA_PCTL_R &= ~0x000FFF00;
GPIO_PORTB_PCTL_R &= ~0xF00F000;
GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
GPIO_PORTD_PCTL_R &= ~0xFF000000;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTA_DATA_R &= ~0x1C;
GPIO_PORTB_DATA_R &= ~0x48;
GPIO_PORTC_DATA_R &= ~0xF0;
GPIO_PORTD_DATA_R &= ~0xC0;
GPIO_PORTF_DATA_R &= ~0x0E;
}


int main()
{
	
}
