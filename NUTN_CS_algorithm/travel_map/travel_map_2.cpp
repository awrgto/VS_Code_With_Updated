#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const float initLongitude = 120.1, initLatitude = 22.9, degree2radius = 3.14159265358979f / 180.0f;

typedef struct point {
    float x, y;
} Point;

std::vector<Point> poi, ch;
float              cross(Point, Point, Point);

int main(void) {
    std::ifstream inputFile("input");
    if (!inputFile.is_open( )) return -99;
    while (inputFile.good( )) {
        float x, y;
        inputFile >> y >> x;
        poi.push_back(
            {degree2radius * (x - initLongitude) * (cos(degree2radius * (x + initLongitude) / 2)) * 6371, degree2radius * (y - initLatitude) * 6371});
    }
    inputFile.close( );
    std::sort(poi.begin( ), poi.end( ), [](const Point a, const Point b) -> bool { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });

    for (std::vector<Point>::iterator iter = poi.begin( ); iter != poi.end( ); iter++) {  // l Convex Hull
        while (ch.size( ) >= 2 && cross(*(ch.end( ) - 2), ch.back( ), *iter) <= 0) ch.pop_back( );
        ch.push_back(*iter);
    }
    int lowwerRecorder = ch.size( ) + 1;

    for (std::vector<Point>::reverse_iterator r_iter = poi.rbegin( ); r_iter != poi.rend( ); r_iter++) {  // will reCount start point for cal area
        while (ch.size( ) >= lowwerRecorder && cross(*(ch.end( ) - 2), ch.back( ), *r_iter) <= 0) ch.pop_back( );
        ch.push_back(*r_iter);
    }
    float area = 0.0;

    for (std::vector<Point>::iterator iter = ch.begin( ); iter != ch.end( ) - 1; iter++) area += cross({0.0, 0.0}, *iter, *(iter + 1));

    float maxDistance = 0.0;
    for (std::vector<Point>::iterator iter = ch.begin( ); iter != ch.end( ) - 1; iter++) {
        for (std::vector<Point>::iterator i_iter = iter; i_iter != ch.end( ) - 1; i_iter++) {
            float tempD = sqrt(pow((iter->x - i_iter->x), 2.0) + pow((iter->y - i_iter->y), 2.0));
            maxDistance = (maxDistance < tempD) ? tempD : maxDistance;
        }
    }

    std::cout << fixed << setprecision(3) << "area of tsp is " << std::fabs(area) / 2.0 << " km^2" << std::endl;
    std::cout << fixed << setprecision(3) << "maxDistance of CH is " << maxDistance << " km";
}

float cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
} 