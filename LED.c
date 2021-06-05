
#include "tm4c123gh6pm_registers.h"


/* Enable PF1 (RED LED) */
void Led_Red_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= ~(1<<1);      /* Disable Analog on PF1 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFFFF0F;   /* Clear PMCx bits for PF1 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= (1<<1);       /* Configure PF1 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<1);      /* Disable alternative function on PF1 */
    GPIO_PORTF_DEN_REG   |= (1<<1);       /* Enable Digital I/O on PF1 */
    GPIO_PORTF_DATA_REG  &= ~(1<<1);      /* Clear bit 1 in Data regsiter to turn off the led */
}

int main(void)
{

    /* Enable clock for PORTF and allow time for clock to start*/
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000020;
    delay = SYSCTL_REGCGC2_REG;


    /* Initailize the SW2 and Red LED as GPIO Pins */
    Led_Red_Init(); 

    double X ;
	

        if(X >= 100)
        {
            GPIO_PORTF_DATA_REG |= 0x00000020;  /* LED RED ON */
        }
    
}
