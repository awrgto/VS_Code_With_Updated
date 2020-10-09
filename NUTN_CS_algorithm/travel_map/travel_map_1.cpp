#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#define p 2

using namespace std;

typedef struct point {
    double x, y;
} Point;

double v_distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };

int main(void) {
    std::vector< Point > poi;
    std::ifstream inputFile("POIs_twd97tm2");
    if (!inputFile.is_open( )) return -99;
    double minDistance = std::numeric_limits< double >::max( );
    int pr               = p;
    while (inputFile.good( ) && pr--) {
        double x, y;
        inputFile >> x >> y;
        poi.push_back({x, y});
    }
    for(auto o : poi)
        for (auto i : poi){
            double tempDistance = v_distance(o, i);
            if (tempDistance == 0) continue;
            if (tempDistance < minDistance) minDistance = tempDistance;
        }
    std::cout << "minDistance of two poi is " << minDistance << " m\n";
}