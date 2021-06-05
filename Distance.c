
#include <stdio.h>
#include <math.h>
#include "tm4c123gh6pm_registers.h"

#define PI = 3.141592653589;

using namespace std;

/* Enable PF0 (SW) */
void SW_Init(void)
{
    GPIO_PORTF_LOCK_REG = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG |= (1 << 0);       /* Enable changes on PF0 */
    GPIO_PORTF_AMSEL_REG &= ~(1 << 0);      /* Disable Analog on PF0 */
    GPIO_PORTF_PCTL_REG &= 0xFFFFFFF0;   /* Clear PMCx bits for PF0 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG &= ~(1 << 0);      /* Configure PF0 as input pin */
    GPIO_PORTF_AFSEL_REG &= ~(1 << 0);      /* Disable alternative function on PF0 */
    GPIO_PORTF_PUR_REG |= (1 << 0);       /* Enable pull-up on PF0 */
    GPIO_PORTF_DEN_REG |= (1 << 0);       /* Enable Digital I/O on PF0 */
}

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

int main(void)
{
    double get_distance;
    double latNew; /* the latitude of the current point the GPS is locating*/
    double lonNew; /* the longitude of the current point the GPS locating */
    double latOld; /* the latitude of the previous point that the GPS located */
    double lonOld; /* the longitude of the previous point that the GPS located*/
    double distance; /* distance between the current point and the point before it */
    double get_distance; /* total distance */
    SW_Init(); /* Initialize the SW switch as GPIO Pin */

   /* double slope[]; */
   /* slope[i] = (latitude[i + 1] - latitude[i]) / (longitude[i + 1] - longitude[i]); */
    
    while (1)
    {
        if (!(GPIO_PORTF_DATA_REG & (1 << 0))) /* if switch is on,  start calculating distance */
        {
            latOld = GPS_lat;
            lonOld = GPS_lon; /* initialize latOld and lonOld with GPS first coordinates */
            get_distance = 0; /* reset total distance to 0 */
            while (get_distance <= 100)
            {
                latNew = GPS_lat; /* reading latitude from GPS */
                lonNew = GPS_lon; /* reading longitude from GPS */
                distance = dist(latOld, lonOld, latNew, lonNew); /* calculate distance between current point and previous one */
                get_distance = get_distance + distance; /* add the distance to the total distance */
                lonOld = lonNew;
                latOld = latNew; /* make the current point the previous one for the next iteration of the loop */
            }
        }
    }
}

