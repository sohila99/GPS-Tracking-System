
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
