#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#define p 12

using namespace std;

typedef struct point {
    double x, y;
} Point;

std::vector< Point > poi, ch;

double cross(Point o, Point a, Point b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
double dot(Point o, Point a, Point b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
double v_distance(Point a, Point b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
void poi_permutation(int*, int, int, double*, double[][p]);
void swap(int* a, int* b);

int main(void) {
    std::ifstream inputFile("POIs_twd97tm2");
    if (!inputFile.is_open( )) return -99;
    double minDistance   = std::numeric_limits< double >::max( );
    double poi_map[p][p] = {{0}};
    int poi_index[p]     = {0};
    int pr               = p;
    while (inputFile.good( ) && pr--) {
        double x, y;
        inputFile >> x >> y;
        poi.push_back({x, y});  //{degree2radius * (x - initLongitude) * (cos(degree2radius * (x + initLongitude) / 2)) * 6371, degree2radius * (y - initLatitude) * 6371});
    }
    inputFile.close( );
    for (size_t iter = 0; iter < p; iter++) poi_index[iter] = iter;
    for (auto o_iter : poi_index)
        for (auto i_iter : poi_index) poi_map[o_iter][i_iter] = v_distance(poi[o_iter], poi[i_iter]);

    poi_permutation(poi_index, 0, p - 1, &minDistance, poi_map);

    std::cout << "minDistance of tsp is " << minDistance << " m";
}
void poi_permutation(int poi_index[], int a, int b, double* minDistance, double map[][p]) {
    if (a == b) {
        double tmpDistance = 0;
        for (size_t iter = 0; iter < p - 1; iter++) {
            //printf("%d %lf\t", poi_index[iter], tmpDistance);
            tmpDistance += map[poi_index[iter]][poi_index[iter + 1]];
        }
        tmpDistance += map[poi_index[0]][(poi_index[p - 1])];
        //printf("%d \n%lf", poi_index[p - 1], tmpDistance);
        if (tmpDistance < *minDistance) *minDistance = tmpDistance;
    }
    else {
        for (int j = a; j < p; j++) {
            swap(&poi_index[a], &poi_index[j]);
            poi_permutation(poi_index, a + 1, b, minDistance, map);
            swap(&poi_index[a], &poi_index[j]);
        }
    }
}
void swap(int* a, int* b) {
    int c = *a;
    *a    = *b;
    *b    = c;
}