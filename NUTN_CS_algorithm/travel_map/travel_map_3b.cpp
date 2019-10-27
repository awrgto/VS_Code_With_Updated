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

std::vector< Point > poi, cp;
std::vector< std::vector< Point > > ch;
float cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
float dot(Point o, Point a, Point b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
float v_distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
float v_height(Point o, Point a, Point b) { return std::fabs(cross(o, a, b)) / v_distance(a, o); };
float v_base(Point o, Point a, Point b) { return std::fabs(dot(o, a, b)) / v_distance(a, o); };

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

    for (std::vector< Point >::iterator iter = poi.begin( ); iter != poi.end( ); iter++) {  // l Convex Hull
        while (ch.size( ) >= 2 && cross(((ch.end( ) - 2)->front( )), ch.back( ).front( ), *iter) <= 0) ch.pop_back( );
        ch.push_back(std::vector< Point >( ));
        ch.back( ).push_back(*iter);
    }
    int lowwerRecorder = ch.size( ) + 1;

    for (std::vector< Point >::reverse_iterator r_iter = poi.rbegin( ); r_iter != poi.rend( ); r_iter++) {  // will reCount start point for cal area
        while (ch.size( ) >= lowwerRecorder && cross(((ch.end( ) - 2)->front( )), ch.back( ).front( ), *r_iter) <= 0) ch.pop_back( );
        ch.push_back(std::vector< Point >( ));
        ch.back( ).push_back(*r_iter);
    } /*
    for (std::vector< std::vector< Point > >::iterator iter = ch.begin( ); iter != ch.end( ); iter++)
        std::cout << iter->front( ).x << ' ' << iter->front( ).y << std::endl;
    std::cout << std::endl;*/

    for (std::vector< Point >::iterator o_iter = poi.begin( ); o_iter != poi.end( ); o_iter++) {
        int temp = 1;
        for (std::vector< std::vector< Point > >::iterator i_iter = ch.begin( ); i_iter != ch.end( ) && temp; i_iter++)
            if (i_iter->front( ).x == o_iter->x && i_iter->front( ).y == o_iter->y) temp *= 0;

        if (temp) cp.push_back(*o_iter);
    } /*
    for (std::vector< Point >::iterator iter = cp.begin( ); iter != cp.end( ); iter++) std::cout << iter->x << ' ' << iter->y << std::endl;
    std::cout << std::endl;*/

    for (std::vector< Point >::iterator cp_iter = cp.begin( ); cp_iter != cp.end( ); cp_iter++) {
        float minHeight = 99999;
        std::vector< std::vector< Point > >::iterator tempInsertPoint;
        for (std::vector< std::vector< Point > >::iterator ch_iter = ch.begin( ); ch_iter != ch.end( ) - 1; ch_iter++) {
            float tempHeight = v_height(ch_iter->front( ), (ch_iter + 1)->front( ), *cp_iter);
            //std::cout << tempHeight << std::endl;
            if (tempHeight < minHeight) {
                minHeight       = tempHeight;
                tempInsertPoint = ch_iter;
            }
        }
        if (tempInsertPoint->size( ) == 1)
            tempInsertPoint->push_back(*cp_iter);
        else {
            int i = 0;
            while (v_base(tempInsertPoint->front( ), (tempInsertPoint + 1)->front( ), *cp_iter) >
                   v_base(tempInsertPoint->front( ), (tempInsertPoint + 1)->front( ), (*tempInsertPoint)[i]))
                i++;
            tempInsertPoint->insert(tempInsertPoint->begin( ) + i, *cp_iter);
        }
    } /*
    for (std::vector< std::vector< Point > >::iterator o_iter = ch.begin( ); o_iter != ch.end( ); o_iter++)  {      
        for (std::vector< Point >::iterator iter = o_iter->begin( ); iter != o_iter->end( ); iter++)
            std::cout << iter->x << ' ' << iter->y << std::endl;
        std::cout << std::endl;}
    std::cout << std::endl;*/
    float minDistance = 0;
    int mark          = 0;
    Point* lastPtr;
    for (std::vector< std::vector< Point > >::iterator o_iter = ch.begin( ); o_iter != ch.end( ); o_iter++)
        for (std::vector< Point >::iterator iter = o_iter->begin( ); iter != o_iter->end( ); iter++) {
            if (!(mark++)) {
                lastPtr = &(*iter);
                continue;
            }
            minDistance += v_distance(*lastPtr, *iter);
            //std::cout << "maxDistance of tsp is " << v_distance(*lastPtr, *iter) << " km";
            lastPtr = &(*iter);
        }
    std::cout << "minDistance of tsp is... " << minDistance << " km";
}