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

void Receive_GPS_Data();

int main(void)
{
	char str[] = GPS_Data();
	systick();
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
	char str[] = GPS_Data();
	systick();
	Receive_GPS_Data(str);
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


