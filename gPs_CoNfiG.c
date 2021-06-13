#include "tm4c123gh6pm_registers.h"
#include "ASCII.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <stdint.h>

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

u_int8_t GPS_Data(void)
{
	while (UART1_Available() != 1);
	return (uint8_t)(UART1_DR_R & 0xFF);
}


u_int8_t char2int(char c)
{
	if (c >= 0x30 && c <= 0x39)
	{
		c = c - 0x30;
	}
	return c;
}

double lat2int(lat)
{
	double deg = char2int(lat[0]) * 10 + char2int(lat[1]);
	double min = char2int(lat[2]) * 10 + char2int(lat[3]) + char2int(lat[5]) * 0.1 + char2int(lat[6]) * 0.01 + char2int(lat[7]) * 0.001;
	deg = deg + min/60;
	return deg;
}

void Receive_GPS_Data(char str)
{
  char* ID = strtok(str,",");
 char* Current_Lat = strtok(NULL,",");
 char* N_S = strtok(NULL,",");
 char* Current_Lon = strtok(NULL,",");
 char* E_W = strtok(NULL,",");
 char* Checksum = strtok(NULL,",");


 if ( strcmp(ID, "$GPGLL")==0 ){


 Latitude = atof(Current_Lat);
 Longitude = atof(Current_Lon);
    
    }
  }
}
}
