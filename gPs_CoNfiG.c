#include "tm4c123gh6pm_registers.h"
#include "ASCII.c"
#include "systick.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <stdint.h>

int Gpsdata;             // for incoming serial data
double Longitude;
double Latitude;

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

unsigned char GPS_Data_Available(void)
{
	return ((UART1_FR_R & 0x00000010) == 0x00000010) ? 0 : 1;
}

char GPS_Data(void)
{
	int i=0;
	char* str[500];
	while ( i<=strlen(str) )
	{
	  	while (GPS_Data_Available() != 1);
		{
			str[i] = ( UART1_DR_R & 0xFF );
			i++;
		}
	}
			return (str);
}

void Receive_GPS_Data(char* str)
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
 int x = floor(Latitude/100);
 double y = (Latitude - x*100)/60;
 Latitude = x+ y;
 if (strcmp(N_S, "S")==0){
 Latitude =-1*Latitude;}
 y = floor(Longitude/100);
 y = (Longitude - x*100)/60;
 Longitude = x+ y;
 if (strcmp(E_W, "W")==0){
 Longitude =-1*Longitude;
    }
	}
}

int main ()
{
	char str[] = GPS_Data();
	systcik();
	Receive_GPS_Data(str);
}
