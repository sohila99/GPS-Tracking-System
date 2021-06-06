#include <stdint.h>
#include "C:/Users/Sohaila/Downloads/project embedded/tm4c123gh6pm.h"
void SystemInit(){}
void delay_ms(int x) //delay in milliseconds 
	{
		int i;
		int j;
		for(i=0 ; i<x ; i++)
		{
			for(j=0 ; j<3180 ; j++)
			{
			}
		}
	}
void delay_us(int x) //delay in microseconds 
	{
		int i;
		int j;
		for(i=0 ; i<x ; i++)
		{
			for(j=0 ; j<3 ; j++)
			{
			}
		}
	}
void LCD_command(unsigned char comm)
{
GPIO_PORTA_DATA_R=0x00;
GPIO_PORTB_DATA_R=comm;
GPIO_PORTA_DATA_R|=0x03;
delay_us(0);
GPIO_PORTA_DATA_R=0x00;
if(comm<4) 
	delay_ms(2);
else 
	delay_us(40);
}

void LCD_data(unsigned char data)
{
GPIO_PORTA_DATA_R=0x10;
GPIO_PORTB_DATA_R=data;
GPIO_PORTA_DATA_R|=0x03;
delay(0);
GPIO_PORTA_DATA_R=0x00;
}

void LCD_Init(void)
{
SYSCTL_RCGCGPIO_R|=0x03;
while((SYSCTL_PRGPIO_R&0X03)==0)
GPIO_PORTB_DIR_R|=0xFF;
GPIO_PORTB_DEN_R|=0xFF;
GPIO_PORTB_AMSEL_R&= ~0XFF;
GPIO_PORTB_AFSEL_R&= ~0XFF;
GPIO_PORTB_PCTL_R&=~0xFFFFFFFF;
GPIO_PORTA_DIR_R|=0x1C;
GPIO_PORTA_DEN_R|=0x1C;
GPIO_PORTA_AMSEL_R&= ~0X1C;
GPIO_PORTA_AFSEL_R&= ~0X1C;
GPIO_PORTA_PCTL_R&=~0x000FFF00; 
LCD_command (0x38);
	delay_us(40);
LCD_command (0x06);
	delay_us(40);
LCD_command (0x01);
	delay_us(40);
LCD_command (0x0F);
	delay_us(40);
LCD_command (0x30);
	delay_us(40);
}

int main()
{
	LCD_Init();
	LCD_command(0x01);
	LCD_command(0x80);
	delay_ms(500);
}
