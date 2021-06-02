#include <stdint.h>
#include "C:/Users/Sohaila/Downloads/project embedded/tm4c123gh6pm.h"
void SystemInit(){}
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
void LCD_command(char comm)
{
GPIO_PORTA_DATA_R=0x00;
GPIO_PORTB_DATA_R=comm;
GPIO_PORTA_DATA_R|=0x03;
delay(100);
GPIO_PORTA_DATA_R=0x00;
}

void LCD_data(char data)
{
GPIO_PORTA_DATA_R=0x10;
GPIO_PORTB_DATA_R=data;
GPIO_PORTA_DATA_R|=0x03;
delay(100);
GPIO_PORTA_DATA_R=0x00;
}

void init(void)
{
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

int main ()
{

}
