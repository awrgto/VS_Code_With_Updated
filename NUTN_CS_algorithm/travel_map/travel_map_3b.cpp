#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

#define p 30

using namespace std;

typedef struct point {
    double x, y;
} Point;

std::vector< Point > poi, cp;
std::vector< std::list< Point > > ch_i;

double cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
double dot(Point o, Point a, Point b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
double v_distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
double v_height(Point o, Point a, Point b) { return std::fabs(cross(o, a, b)) / v_distance(a, o); };
double v_base(Point o, Point a, Point b) { return std::fabs(dot(o, a, b)) / v_distance(a, o); };

int main(void) {
    std::ifstream inputFile("POIs_twd97tm2");
    if (!inputFile.is_open( )) return -99;
    int pr = p;
    while (inputFile.good( ) && pr--) {
        double x, y;
        inputFile >> x >> y;
        poi.push_back({x, y});  //{degree2radius * (x - initLongitude) * (cos(degree2radius * (x + initLongitude) / 2)) * 6371, degree2radius * (y - initLatitude) * 6371});
    }
    inputFile.close( );
    std::sort(poi.begin( ), poi.end( ), [](const Point a, const Point b) -> bool { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });

    for (auto iter : poi) std::cout << fixed << setprecision(4) << iter.x << ' ' << iter.y << std::endl;
    std::cout << std::endl;
    for (auto element : poi) {  // l Convex Hull
        while (ch_i.size( ) >= 2 && cross(((ch_i.end( ) - 2)->front( )), ch_i.back( ).front( ), element) <= 0) ch_i.pop_back( );
        ch_i.push_back(std::list< Point >( ));
        ch_i.back( ).push_back(element);
    }
    int lowwerRecorder = ch_i.size( ) + 1;

    for (auto r_iter = poi.rbegin( ); r_iter != poi.rend( ); r_iter++) {  // will reCount start point for cal area
        while (ch_i.size( ) >= lowwerRecorder && cross(((ch_i.end( ) - 2)->front( )), ch_i.back( ).front( ), *r_iter) <= 0) ch_i.pop_back( );
        ch_i.push_back(std::list< Point >( ));
        ch_i.back( ).push_back(*r_iter);
    }
    for (auto iter : ch_i) std::cout << iter.front( ).x << ' ' << iter.front( ).y << std::endl;
    std::cout << std::endl;
    for (auto o_iter = poi.begin( ); o_iter != poi.end( ); o_iter++) {
        int temp = 1;
        for (auto i_iter = ch_i.begin( ); i_iter != ch_i.end( ) && temp; i_iter++)
            if (i_iter->front( ).x == o_iter->x && i_iter->front( ).y == o_iter->y) temp *= 0;
        if (temp) cp.push_back(*o_iter);
    }
    for (auto iter : cp) std::cout << iter.x << ' ' << iter.y << std::endl;
    std::cout << std::endl;

    for (auto cp_ele : cp) {
        double minHeight     = std::numeric_limits< double >::max( );
        auto tempInsertPoint = ch_i.begin( );
        for (auto ch_i_iter = ch_i.begin( ); ch_i_iter != ch_i.end( ) - 1; ch_i_iter++) {
            double tempHeight = v_height(ch_i_iter->front( ), (ch_i_iter + 1)->front( ), cp_ele);
            //std::cout << tempHeight << std::endl;
            if (tempHeight < minHeight) {
                minHeight       = tempHeight;
                tempInsertPoint = ch_i_iter;
            }
        }
        if (tempInsertPoint->size( ) == 1)
            tempInsertPoint->push_back(cp_ele);
        else {
            auto listPtr = begin(*tempInsertPoint);
            while (v_base(tempInsertPoint->front( ), (tempInsertPoint + 1)->front( ), cp_ele) > v_base(tempInsertPoint->front( ), (tempInsertPoint + 1)->front( ), *(listPtr)))
                listPtr++;
            tempInsertPoint->insert(listPtr, cp_ele);
        }
    }
    for (auto o_iter : ch_i) {
        for (auto iter : o_iter)
            std::cout << iter.x << ' ' << iter.y << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl;

    double minDistance = 0;
    int mark           = 0;
    Point lastPtr      = {0, 0};
    for (auto o_iter : ch_i)
        for (auto iter : o_iter) {
            if (!(mark++)) {
                lastPtr = iter;
                continue;
            }
            minDistance += v_distance(lastPtr, iter);
            //std::cout << "maxDistance of tsp is " << v_distance(*lastPtr, *iter) << " km";
            lastPtr = iter;
        }
    std::cout << fixed << setprecision(4) << "minDistance of tsp is... " << minDistance << " m";
}