#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int p = 20;
typedef struct point {
    double x, y;
} Point;

std::vector< Point > poi, ch;
double cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };

int main(void) {
    std::ifstream inputFile("POIs_twd97tm2");
    if (!inputFile.is_open( )) return -99;
    int pr                  = p;
    double area        = 0.0;
    double maxDistance = 0.0;
    while (inputFile.good( ) && pr--) {
        double x, y;
        inputFile >> x >> y;
        poi.push_back({x, y});  //{degree2radius * (x - initLongitude) * (cos(degree2radius * (x + initLongitude) / 2)) * 6371, degree2radius * (y - initLatitude) * 6371});
    }
    inputFile.close( );
    std::sort(poi.begin( ), poi.end( ), [](const Point a, const Point b) -> bool { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });
    // l Convex Hull
    for (auto element : poi) {                                                                        //ele will run out poi
        while (ch.size( ) >= 2 && cross(*(ch.end( ) - 2), ch.back( ), element) <= 0) ch.pop_back( );  // continue del illegal node
        ch.push_back(element);
    }
    int lowwerRecorder = ch.size( ) + 1;

    for (auto r_iter = poi.rbegin( ); r_iter != poi.rend( ); r_iter++) {                                           // will reCount start point for cal area
        while (ch.size( ) >= lowwerRecorder && cross(*(ch.end( ) - 2), ch.back( ), *r_iter) <= 0) ch.pop_back( );  // continue del illegal node
        ch.push_back(*r_iter);
    }

    for (auto iter = ch.begin( ); iter != ch.end( ) - 1; iter++) area += cross({0.0, 0.0}, *iter, *(iter + 1));

    for (auto iter : ch) {
        for (auto i_iter : ch) {
            double tempD = sqrt(pow((iter.x - i_iter.x), 2.0) + pow((iter.y - i_iter.y), 2.0));
            if (tempD > maxDistance) maxDistance = tempD;
        }
    }

    std::cout << fixed << setprecision(4) << "(assume earth is a ball)area of CH is " << std::fabs(area) / 2.0 / 1000000 << " km^2" << std::endl;
    std::cout << fixed << setprecision(4) << "(assume earth is a ball)maxDistance of CH is " << maxDistance << " m";
}