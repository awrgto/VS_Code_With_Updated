#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

#define p 30
#define r 500
#define k 1

using namespace std;

typedef struct point {
    double x, y;
} Point;

typedef std::vector< int > VI;
typedef std::vector< Point > VP;
typedef std::vector< std::list< Point > > VLP;

VP index_to_VP(VI data_index, VP data);
VLP to_convex_hull(VP data);
double Length_of_group(VP data);

double cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
double dot(Point o, Point a, Point b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
double v_distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
double v_height(Point o, Point a, Point b) { return std::fabs(cross(o, a, b)) / v_distance(a, o); };
double v_base(Point o, Point a, Point b) { return std::fabs(dot(o, a, b)) / v_distance(a, o); };

int main(void) {
    VP poi;
    VI group[p];
    std::list< int > poi_copy;

    std::ifstream inputFile("POIs_twd97tm2");
    if (!inputFile.is_open( )) return -99;
    int poi_index[p]     = {0};
    double poi_map[p][p] = {{0}};
    int pr               = p;
    while (inputFile.good( ) && pr--) {
        double x, y;
        inputFile >> x >> y;
        poi.push_back({x, y});
    }
    inputFile.close( );
    std::sort(poi.begin( ), poi.end( ), [](const Point a, const Point b) -> bool { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });

    for (size_t iter = 0; iter < p; iter++) poi_index[iter] = iter;
    for (auto o_iter : poi_index)
        for (auto i_iter : poi_index) poi_map[o_iter][i_iter] = v_distance(poi[o_iter], poi[i_iter]) <= r;

    for (const auto& ele : poi_index) poi_copy.push_back(ele);

    int now_loop_group = 0;

    while (poi_copy.size( )) {  //cout << poi_copy.size( ) << " i\n";
        group[now_loop_group].push_back(poi_copy.front( ));
        poi_copy.pop_front( );
        for (size_t i = 0; i < group[now_loop_group].size( ); i++) {
            auto iter    = group[now_loop_group].begin( ) + i;
            int temp[30] = {0}, temp_index = 0;  //std::cout << *iter << "iterS\n";
            for (auto j : poi_copy)
                if (poi_map[*iter][j])
                    temp[temp_index++] = j;
            for (size_t temp_i = 0; temp_i < temp_index; temp_i++) {
                group[now_loop_group].push_back(temp[temp_i]);  //std::cout << "\t\t" << temp[temp_i] << "iterS\n";
                poi_copy.remove(temp[temp_i]);
            }
        }
        now_loop_group++;  //cout << "w " << poi_copy.size( ) << " f\n";
    }

    double total_wolk_length  = 0.0;
    double total_drive_length = 0.0;
    VP group_4_car;
    group_4_car.reserve(now_loop_group);

    for (auto submenber_of_group : group)
        if (submenber_of_group.size( ) >= k) {
            total_wolk_length += Length_of_group(index_to_VP(submenber_of_group, poi));
            group_4_car.push_back(poi[submenber_of_group.front( )]);
        }

    total_drive_length = Length_of_group(group_4_car);

    std::cout << fixed << setprecision(4) << "Distance of tsp by wolk is... " << total_wolk_length << " m\n";
    std::cout << "Distance of tsp by car is... " << total_drive_length << " m";
}
VP index_to_VP(VI data_index, VP data) {
    VP tempVP;
    tempVP.reserve(data_index.size( ));
    for (auto index : data_index) tempVP.push_back(data[index]);
    return tempVP;
}
double Length_of_group(VP data) {
    VLP CH = to_convex_hull(data);
    VP cp;
    for (auto o_iter = data.begin( ); o_iter != data.end( ); o_iter++) {
        int temp = 1;
        for (auto i_iter = CH.begin( ); i_iter != CH.end( ) && temp; i_iter++)
            if (i_iter->front( ).x == o_iter->x && i_iter->front( ).y == o_iter->y) temp *= 0;
        if (temp) cp.push_back(*o_iter);
    }
    for (auto cp_ele : cp) {
        double minHeight     = std::numeric_limits< double >::max( );
        auto tempInsertPoint = CH.begin( );
        for (auto CH_iter = CH.begin( ); CH_iter != CH.end( ) - 1; CH_iter++) {
            double tempHeight = v_height(CH_iter->front( ), (CH_iter + 1)->front( ), cp_ele);  //std::cout << tempHeight << std::endl;
            if (tempHeight < minHeight) {
                minHeight       = tempHeight;
                tempInsertPoint = CH_iter;
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
    double minDistance = 0;
    int mark           = 0;
    Point lastPtr      = {0, 0};
    for (auto o_iter : CH)
        for (auto iter : o_iter) {
            if (!(mark++)) {
                lastPtr = iter;
                continue;
            }
            minDistance += v_distance(lastPtr, iter);            //std::cout << "\t\tmaxDistance of tsp is " << v_distance(lastPtr, iter) << " m\n";
            lastPtr = iter;
        }  //std::cout << "\tsG... " << minDistance << " m\n";
    return minDistance;
};
VLP to_convex_hull(VP data) {
    VLP CH;

    std::sort(data.begin( ), data.end( ), [](const Point a, const Point b) -> bool { return (a.x < b.x) || (a.x == b.x && a.y < b.y); });

    /*for (auto iter : data) std::cout << fixed << setprecision(4) << iter.x << ' ' << iter.y << std::endl;
    std::cout << std::endl;*/
    for (auto element : data) {  // l Convex Hull
        while (CH.size( ) >= 2 && cross(((CH.end( ) - 2)->front( )), CH.back( ).front( ), element) <= 0) CH.pop_back( );
        CH.push_back(std::list< Point >( ));
        CH.back( ).push_back(element);
    }
    int lowwerRecorder = CH.size( ) + 1;

    for (auto r_iter = data.rbegin( ); r_iter != data.rend( ); r_iter++) {  // will reCount start point for cal area
        while (CH.size( ) >= lowwerRecorder && cross(((CH.end( ) - 2)->front( )), CH.back( ).front( ), *r_iter) <= 0) CH.pop_back( );
        CH.push_back(std::list< Point >( ));
        CH.back( ).push_back(*r_iter);
    }
    return CH;
}