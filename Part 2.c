#include "tm4c123gh6pm_registers.h"
#include "ASCII.c"
#include "systick.c"
#include <distance.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <GPS.h>
#define PI = 3.141592653589;

int Gpsdata;             // for incoming serial data
double Longitude;
double Latitude;

void LED(void)    //set leds
{
 SYSCTL_RCGCGPIO_R |= 0x20;
 while ((SYSCTL_PRGPIO_R&0x20)==0){};
 GPIO_PORTF_LOCK_R = 0x4C4F434B;
 GPIO_PORTF_CR_R |= 0x02;
 GPIO_PORTF_DIR_R |= 0x02;
 GPIO_PORTF_DEN_R |= 0x02;
 GPIO_PORTF_AMSEL_R =~0x02;
 GPIO_PORTF_AFSEL_R = ~0x02;
 GPIO_PORTF_PCTL_R &= ~0x000000F0;
    GPIO_PORTF_PUR_R |= 0x02;

}
void led_out(unsigned char data ){


            GPIO_PORTF_DATA_R|=data;

void delay_micro(int n);
void delay_milli(int n);
void LCD_PORT_INIT();
void LCD_COM(unsigned char cpm);
void LCD_DATA(unsigned char data);

void LCD_DATA(unsigned char data)
{
    GPIO_PORTA_DATA_R=0x04;
    GPIO_PORTB_DATA_R=data;
    GPIO_PORTA_DATA_R|=0x10;
    delay_micro(0);
    GPIO_PORTA_DATA_R=0x00;
}

void LCD_COM(unsigned char com)
{
    GPIO_PORTA_DATA_R=0x00;
    GPIO_PORTB_DATA_R=com;
    GPIO_PORTA_DATA_R=0x10;
    delay_micro(0);
        GPIO_PORTA_DATA_R=0x00;
    if(com <4) delay_milli(2); else delay_micro(37);
}
void LCD_PORT_INIT()
{
    SYSCTL_RCGCGPIO_R|=0x03;
    while((SYSCTL_PRGPIO_R&0X03)==0){}
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
       delay_micro(37);
    LCD_COM(0x38);
         delay_micro(37);
  LCD_COM(0x06);
         delay_micro(37);
  LCD_COM(0x01);
         delay_micro(37);
  LCD_COM(0x0F);
         delay_micro(37);
    LCD_COM(0x30);
         delay_micro(37);
 }

    void delay_milli(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3180;j++)
{}
}
void delay_micro(int n){
int i,j;
for(i=0;i<n;i++)
for(j=0;j<3;j++)
{}
}

void Receive_GPS_Data();

int main(void)
{
    double get_distance;
    double lat_new; /* the latitude of the current point the GPS is locating*/
    double lon_new; /* the longitude of the current point the GPS locating */
    double lat_old; /* the latitude of the previous point that the GPS located */
    double lon_old; /* the longitude of the previous point that the GPS located*/
    double distance; /* distance between the current point and the point before it */
    double get_distance; /* total distance */
    delay_milli(50);
	
    while (1)
    {
	LCD_PORT_INIT();
	LCD_COM(1); /* clear display */
	LCD_COM(0x80); /* lcd cursor location */
	delay_milli(50);
	char str[] = GPS_Data();
	systick();
	lat_lon[] = Receive_GPS_Data(str);
	double GPS_lat = lat_lon[0];
	double GPS_lon = lat_lon[1];
        lat_old = GPS_lat;
        lon_old = GPS_lon; /* initialize latOld and lonOld with GPS first coordinates */
        get_distance = 0; /* reset total distance to 0 */
	char LCD_dist[11] = "dist = xxxx";
    	while (get_distance <= 100)
        {
		lat_new = GPS_lat; /* reading latitude from GPS */
                lon_new = GPS_lon; /* reading longitude from GPS */
                distance = dist(lat_old, lon_old, lat_new, lon_new); /* calculate distance between current point and previous one */
                get_distance = get_distance + distance; /* add the distance to the total distance */
		LCD dist[7] = dist_ASCII_b3(get_distance);
		LCD dist[8] = dist_ASCII_b2(get_distance);
		LCD dist[9] = dist_ASCII_b1(get_distance);
		LCD dist[10] = dist_ASCII_b0(get_distance);
                lon_old = lon_new;
                lat_old = lat_new; /* make the current point the previous one for the next iteration of the loop */
                wait();
		str[] = GPS_Data();
		systick();
		lat_lon[] = Receive_GPS_Data(str);
		GPS_lat = lat_lon[0];
		GPS_lon = lat_lon[1];
        }
        double destination_lat = lat_new;
        double destination_lon = lon_new;         
        }
    }
    return 0;
}


