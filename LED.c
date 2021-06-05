
#include "tm4c123gh6pm_registers.h"


/* Enable PF1 (RED LED) */
void Led_Red_Init(void)
{
	SYSCTL_REGCGC2_REG |= 0x00000020;
  	GPIO_PORTF_LOCK_REG = 0x4C4F434B;
	GPIO_PORTF_CR_REG =0x1F;
	GPIO_PORTF_AFSEL_REG =0;
	GPIO_PORTF_PCTL_REG =0;
	GPIO_PORTF_AMSEL_REG=0;
	GPIO_PORTF_DIR_REG=0X0E;
	GPIO_PORTF_PUR_REG=0X11;
	GPIO_PORTF_DEN_REG =0X1F;

}
double distance;

void Turn_On(double distance)
{
	if (distance>=100)
	{
		GPIO_PORTF_DATA_REG |= (1<<1);
	}
}
int main(void)
{
	while (1)
		{
			Led_Red_Init();  
			Turn_On(90);			
		}
}
