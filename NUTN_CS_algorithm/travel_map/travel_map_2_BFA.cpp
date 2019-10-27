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

std::vector< Point > poi, ch;
float cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
float dot(Point o, Point a, Point b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
float distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };

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
    ch.push_back(poi.front( ));
    for (std::vector< Point >::iterator iter = poi.begin( ); iter != poi.end( ); iter++) {
        if ((ch[0].y < iter->y) || (ch[0].y == iter->y && ch[0].x < iter->x)) ch[0] = *iter;
    }
    float maxDistance = 0;
    Point tempCh = (Point){0.0, 0.0}, lastCh = (Point){0.0, ch.front( ).y};
    while (!((ch.back( ).x == ch.front( ).x) && (ch.back( ).y == ch.front( ).y) && (ch.size( ) > 1))) {
        float cosDegree = 2;
        for (std::vector< Point >::iterator iter = poi.begin( ); iter != poi.end( ); iter++) {
            if ((ch.back( ).x == iter->x) && (ch.back( ).y == iter->y)) continue;
            float tempDegree   = dot(ch.back( ), lastCh, *iter) / (distance(lastCh, ch.back( )) * distance(ch.back( ), *iter));
            float tempDistance = distance(ch.back( ), *iter);
            if (tempDegree < cosDegree) {
                cosDegree = tempDegree;
                tempCh    = *iter;
            }
            maxDistance = (maxDistance < tempDistance ? tempDistance : maxDistance);
        }
        lastCh = ch.back( );
        ch.push_back(tempCh);
    }
    /*debugger
    for (std::vector< Point >::iterator iter = ch.begin( ); iter != ch.end( ); iter++) std::cout << iter->x << "," << iter->y << std::endl;
    std::cout << std::endl;*/
    float area = 0.0;
    for (std::vector< Point >::iterator iter = ch.begin( ); iter != ch.end( ) - 1; iter++) area += cross({0.0, 0.0}, *iter, *(iter + 1));

    std::cout << fixed << setprecision(3) << "area of tsp is " << std::fabs(area) / 2.0 << " km^2" << std::endl;
    std::cout << fixed << setprecision(3) << "maxDistance of tsp is " << maxDistance << " km";
}