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

float minDistance = 10000;
float tmpDistance = 0;
std::vector< Point > poi, ch;
std::vector< int > poi_index;
std::vector< std::vector< float > > poiMap;
float cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
float dot(Point o, Point a, Point b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
float distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
void poi_permutation(int a, int b);

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
    poiMap.resize(poi.size( ));
    poi_index.resize(poi.size( ));
    for (size_t o_iter = 0; o_iter < poi.size( ); o_iter++) {
        poiMap[o_iter].resize(poi.size( ));
        poi_index[o_iter] = o_iter;
        for (size_t i_iter = 0; i_iter < poi.size( ); i_iter++) { poiMap[o_iter][i_iter] = distance(poi[o_iter], poi[i_iter]); }
    }
    poi_permutation(0, poi.size( ) - 1);
    std::cout << fixed << setprecision(3) << "minDistance of tsp is " << minDistance << " km";
}
void poi_permutation(int a, int b) {
    if (a == b) {
        for (std::vector< int >::iterator iter = poi_index.begin( ); iter != poi_index.end( ) - 1; iter++) {
            //cout << *iter;
            tmpDistance += poiMap[*iter][*iter + 1];
        }
        //cout << *(poi_index.end( ) - 1) << endl;
        tmpDistance += poiMap[*poi_index.begin( )][*(poi_index.end( ) - 1)];
        if (tmpDistance < minDistance) minDistance = tmpDistance;
    }
    else{
        for (int j = a; j < poi.size(); j++) {
            std::swap(poi_index[a], poi_index[j]);
            poi_permutation(a + 1, b);
            std::swap(poi_index[a], poi_index[j]);
        }
    }
}