
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

void systick(void)
{
  NVIC_ST_CTRL_R=0; // disable timer
  NVIC_ST_RELOAD_R = 16000-1; // delay time is 1 ms or 16000-1 counts
  NVIC_ST_CURRENT_R = 0; // clear current value & flag
  NVIC_ST_CTRL_R=5; // enable timer
  while (NVIC_ST_CTRL_R & 0x10000==0) {}
}

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

 	if ( strcmp(ID, "$GPGLL")==0 )
	{
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

int main ()
{
	char str[] = GPS_Data();
	systick();
	Receive_GPS_Data(str);
}








#include <stdio.h>
#include <math.h>

#define PI = 3.141592653589;

using namespace std;

/* function to convert from degree to radian */

double deg2rad(double deg) {
    return (deg * PI / 180);
}

/* function to calculate the distance between two coordinates from the GPS */

long double dist(double lat1, double lon1, double lat2, double lon2);
{
    /* converting all coordinates to radian */
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0; /* if it's the same point, the distance between them is zero */
    }
    else {
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        dis = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2); /* Haversine's Formula */
        dis = 2 * asin(sqrt(dis));
        dis = dis * 6371; /* distance in kilometers */
        dis = dis * 1000; /* distance in meters */
        return dis;
    }
}

/* function to wait for the clock */

void wait() {
	int clockCounter = 0;
	while (clockCounter++ < 1000000) {}
}

int main(void)
{
    double get_distance;
    double lat_new; /* the latitude of the current point the GPS is locating*/
    double lon_new; /* the longitude of the current point the GPS locating */
    double lat_old; /* the latitude of the previous point that the GPS located */
    double lon_old; /* the longitude of the previous point that the GPS located*/
    double distance; /* distance between the current point and the point before it */
    double get_distance; /* total distance */
    wait();
    while (1)
    {
        if (GPS_lat > 30.063856 && GPS_lat < 30.063940 && GPS_lon > 31.277541 && GPS_lon < 31.277653) /* margin for starting point */
        {
            lat_old = GPS_lat;
            lon_old = GPS_lon; /* initialize latOld and lonOld with GPS first coordinates */
            get_distance = 0; /* reset total distance to 0 */
            while (get_distance <= 100)
            {
                lat_new = GPS_lat; /* reading latitude from GPS */
                lon_new = GPS_lon; /* reading longitude from GPS */
                distance = dist(lat_old, lon_old, lat_new, lon_new); /* calculate distance between current point and previous one */
                get_distance = get_distance + distance; /* add the distance to the total distance */
                lon_old = lon_new;
                lat_old = lat_new; /* make the current point the previous one for the next iteration of the loop */
                wait();
            }
            double destination_lat = lat_new;
            double destination_lon = lon_new;         
        }
    }
    return 0;
}



char dist_ASCII_b0(int d)
{
    if (d < 0)
    {
        return 0x4E; // if below 0, print "N" of the word "MIN"
    }
    else if (d >= 0 && d < 1000)
    {
        return 0x6D; // if in the correct range, print "m" for meters
    }
    else if (d >= 1000)
    {
        return 0x58; // if above 3-digits, print "X" of the word "MAX"
    }
}

char dist_ASCII_b1(int d)
{
    int a;
    if (d < 0)
    {
        return 0x49; // if below 0, print "I" of the word "MIN"
    }
    else if(d >= 0 && d < 1000)
    {
        a = d % 10; // a = units digit
        a = a + 0x30;
        return a;
    }
    else if(d >= 1000)
    {
        return 0x41; // if above 3-digits, print "A" of the word "MAX"
    }
}

char dist_ASCII_b2(int d)
{
    int a;
    int b;
    if (d >= 1000 || d < 0)
    {
        return 0x4D; // if below 0 or above 3-digits, print "M" of the word "MAX" or "MIN"
    }
    else if(d >= 0 && d < 1000)
    {
        a = d % 100; // a = rightmost 2 digits
        b = d % 10; // b = units digit
        a = a - b; // tenth digit
        a = a / 10;
        a = a + 0x30;
        return a;
    }
}

char dist_ASCII_b3(int d)
{
    int a;
    int b;
    if (d >= 1000 || d < 0)
    {
        return 0x20; // print empty space since "MAX" and "MIN" need only 3 spaces
    }
    if (d >= 0 && d < 1000)
    {
        b = d % 100; // b = rightmost 2 digits
        a = d - b; // a = 3rd digit
        a = a / 100;
        a = a + 0x30;
        return a;
    }
}

int main()
{
    int distance = 250;
    int a = dist_ASCII_b3(distance);
    int b = dist_ASCII_b2(distance);
    int c = dist_ASCII_b1(distance);
    int d = dist_ASCII_b0(distance);
    printf("%c%c%c%c", a, b, c, d);
}

