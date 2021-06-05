
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

