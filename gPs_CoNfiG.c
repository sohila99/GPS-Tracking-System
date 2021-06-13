#include "tm4c123gh6pm_registers.h"
#include "stdint.h"

int Gpsdata;             // for incoming serial data
unsigned int end =0;  // indicate end of message
unsigned int count=0;  // position counter
unsigned int lat_cnt=0;  // latitude data counter
unsigned int log_cnt=0;  // longitude data counter
unsigned int flag    =0;  // GPS flag
unsigned int comma_count=0;  // comma counter
char lat[20];            // latitude array
char lg[20];             // longitude array

void Receive_GPS_Data();


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
	GPIO_PORTC_PCTL_R &= ~0xFF00FFFF;
	GPIO_PORTC_PCTL_R |= 0x00220000;
	GPIO_PORTC_DEN_R |= 0x30;
}

uint8_t GPS_Data_Available(void)
{
	return ((UART1_FR_R & 0x00000010) == 0x00000010) ? 0 : 1;
}

uint8_t GPS_Data(void)
{
	while (UART1_Available() != 1);
	return (uint8_t)(UART1_DR_R & 0xFF);
}


uint8_t char2int(c)
{
	if (c >= 0x30 && c <= 0x39)
	{
		c = c - 0x30;
	}
	return c;
}

void Receive_GPS_Data()
{
  while(end==0){
    while( GPS_Data_Available() == 0){
      Gpsdata = GPS_Data();
      flag = 1;
     if( Gpsdata=='$' && count == 0)   // finding GPGLL header
       count=1;
     if( Gpsdata=='G' && count == 1)
       count=2;
     if( Gpsdata=='P' && count == 2)
       count=3;
     if( Gpsdata=='G' && count == 3)
       count=4;
     if( Gpsdata=='L' && count == 4)
       count=5;
     if( Gpsdata=='L' && count ==5 )
       count=6;
     if(count==6 &&  Gpsdata ==','){   // count commas in message
       comma_count++;
       flag=0;
     }

     if(comma_count==1 && flag==1){
      lat[lat_cnt++] =  Gpsdata;         // latitude
      flag=0;
     }

     if(comma_count==3 && flag==1){
       lg[log_cnt++] =  Gpsdata;         // Longitude
       flag=0;
     }

     if( Gpsdata == '*' && comma_count >= 3){
       comma_count = 0;                      // end of GPGLL message
       lat_cnt = 0;
       log_cnt = 0;
       flag    = 0;
       end     = 1;

    }
  }
}
}
