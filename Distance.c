
/* #include <bits/stdc++.h> */

#include <stdio.h>
#include <math.h>

#define PI = 3.141592653589;

using namespace std;

double deg2rad(double deg) {
    return (deg * pi / 180);
}

double rad2deg(double rad) {
    return (rad * 180 / PI);
}

long double dist(double lat1, double lon1, double lat2, double lon2);
{
    lat1 = deg2rad(lat1);
    lon1 = deg2rad(lon1);
    lat2 = deg2rad(lat2);
    lon2 = deg2rad(lon2);

    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        dis = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
        dis = 2 * asin(sqrt(dis));
        dis = dis * 6371;
        dis = dis * 1000;
        return dis;
    }
}

int main(void)
{
    double get_distance;
    double longitude[] = { 11.1, 12.3, 14.1, 19.1, 9.2, 21.4 };
    double latitude[] = { 51.1, 21.3, 1.1, 14.4, 2.9, 24.1 };
    double distance[];
    
   /* double slope[]; */
   /* slope[i] = (latitude[i + 1] - latitude[i]) / (longitude[i + 1] - longitude[i]); */
       
    while (get_distance <= 100)
            {
                distance[i] = dist(latitude[i], longitude[i], latitude[i + 1], longtitude[i + 1]);
                get_distance = get_distance + distance[i];
                i = i + 1;
            }
}
