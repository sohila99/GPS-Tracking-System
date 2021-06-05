#include <stdio.h>
#include "C:/Keil/ARM/0flash/tm4c123gh6pm.h"
void SystemInit() {}

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

void delay(int x)
	{
		int i;
		int j;
		for(i=0 ; i<x ; i++)
		{
			for(j=0 ; j<x ; j++)
			{
			}
		}
	}
void LCD_command(unsigned char comm)
{
GPIO_PORTA_DATA_R=0x00;
GPIO_PORTB_DATA_R=comm;
GPIO_PORTA_DATA_R|=0x03;
delay(100);
GPIO_PORTA_DATA_R=0x00;
}

void LCD_data(unsigned char data)
{
GPIO_PORTA_DATA_R=0x10;
GPIO_PORTB_DATA_R=data;
GPIO_PORTA_DATA_R|=0x03;
delay(100);
GPIO_PORTA_DATA_R=0x00;
}

void RGBLED_Init ()
{
SYSCTL_RCGCGPIO_R |= 0x2F;
	while ((SYSCTL_PRGPIO_R&0x2F) == 0)
	{
		delay(100);
	}
GPIO_PORTA_LOCK_R = 0x4C4F434B;
GPIO_PORTB_LOCK_R = 0x4C4F434B;
GPIO_PORTC_LOCK_R = 0x4C4F434B;
GPIO_PORTD_LOCK_R = 0x4C4F434B;
GPIO_PORTE_LOCK_R = 0x4C4F434B;
GPIO_PORTF_LOCK_R = 0x4C4F434B;
GPIO_PORTA_CR_R |= 0x1C;
GPIO_PORTB_CR_R |= 0x0C;
GPIO_PORTC_CR_R |= 0xF0;
GPIO_PORTD_CR_R |= 0x40;
GPIO_PORTE_CR_R |= 0x01;
GPIO_PORTF_CR_R |= 0x0E;
GPIO_PORTA_DIR_R |= 0x1C;
GPIO_PORTB_DIR_R |= 0x0C;
GPIO_PORTC_DIR_R |= 0xF0;
GPIO_PORTD_DIR_R |= 0x40;
GPIO_PORTE_DIR_R |= 0x01;
GPIO_PORTF_DIR_R |= 0x0E;
GPIO_PORTA_DEN_R |= 0x1C;
GPIO_PORTB_DEN_R |= 0x0C;
GPIO_PORTC_DEN_R |= 0xF0;
GPIO_PORTD_DEN_R |= 0x40;
GPIO_PORTE_DEN_R |= 0x01;
GPIO_PORTF_DEN_R |= 0x0E;
GPIO_PORTA_AMSEL_R &= ~0x1C;
GPIO_PORTB_AMSEL_R &= ~0x0C;
GPIO_PORTC_AMSEL_R &= ~0xF0;
GPIO_PORTD_AMSEL_R &= ~0x40;
GPIO_PORTE_AMSEL_R &= ~0x01;
GPIO_PORTF_AMSEL_R &= ~0x0E;
GPIO_PORTA_AFSEL_R &= ~0x1C;
GPIO_PORTB_AFSEL_R &= ~0x0C;
GPIO_PORTC_AFSEL_R &= ~0xF0;
GPIO_PORTD_AFSEL_R &= ~0x40;
GPIO_PORTD_AFSEL_R &= ~0x01;
GPIO_PORTF_AFSEL_R &= ~0x0E;
GPIO_PORTA_PCTL_R &= ~0x000FFF00;
GPIO_PORTB_PCTL_R &= ~0x000FF00;
GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
GPIO_PORTD_PCTL_R &= ~0x0F000000;
GPIO_PORTE_PCTL_R &= ~0x00000001;
GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
GPIO_PORTA_DATA_R &= ~0x1C;
GPIO_PORTB_DATA_R &= ~0x0C;
GPIO_PORTC_DATA_R &= ~0xF0;
GPIO_PORTD_DATA_R &= ~0x40;
GPIO_PORTD_DATA_R &= ~0x01;
GPIO_PORTF_DATA_R &= ~0x0E;

GPIO_PORTA_DIR_R=0x1B;
GPIO_PORTA_DEN_R=0x1B;
GPIO_PORTA_DATA_R=0x1B;

LCD_command (0x01);
LCD_command (0x0E);
LCD_command (0x06);
LCD_command (0x80);
LCD_command (0x38);
LCD_command (0x0F);
}
/* Enable PF1 (RED LED) */
void Led_Red_Init(void)
{
	SYSCTL_RCGC2_R |= 0x00000020;
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R =0x1F;
	GPIO_PORTF_AFSEL_R =0;
	GPIO_PORTF_PCTL_R=0;
	GPIO_PORTF_AMSEL_R=0;
	GPIO_PORTF_DIR_R=0X0E;
	GPIO_PORTF_PUR_R=0X11;
	GPIO_PORTF_DEN_R =0X1F;
}

void Turn_On(double distance)
{
	if (distance>=100)
	{
		GPIO_PORTF_DATA_R |= (1<<1);
	}
}

int main()
{
	while (1)
		{
			RGBLED_Init ();
			Led_Red_Init(); 
			Turn_On(200);
			LCD_data('G');
		}
}
