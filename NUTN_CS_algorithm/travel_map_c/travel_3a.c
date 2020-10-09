#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define p 12

typedef struct point_of_interest {
    double x;
    double y;
} POI;

const POI poi_twd97tm2[30] = {
    {168499.2522, 2543803.7769}, {168502.8393, 2544059.6925}, {168087.6590, 2543364.1322}, {168818.8743, 2543104.2208}, {168950.1215, 2542963.5062},
    {169522.5312, 2543034.8114}, {169769.0516, 2543055.3704}, {168246.3564, 2544227.3312}, {163803.1187, 2543189.0074}, {163528.9189, 2543330.5882},
    {162785.3125, 2543334.8820}, {162578.6313, 2543546.0903}, {164069.7493, 2544609.3637}, {163735.6970, 2544475.6571}, {163667.7204, 2544897.1218},
    {163866.8951, 2544912.3843}, {163951.4595, 2544697.5365}, {164399.6450, 2544786.8476}, {164263.4921, 2544443.1072}, {169859.4654, 2544436.2930},
    {169322.3900, 2544687.4339}, {169221.2709, 2544496.5814}, {169324.1495, 2544605.3981}, {169096.8012, 2543237.2597}, {168950.2768, 2543196.4846},
    {168848.7097, 2543740.6368}, {163505.5312, 2543663.2336}, {168424.1674, 2543447.0709}, {157860.5934, 2561516.1911}, {160597.5276, 2552055.1702}};

double v_distance(POI a, POI b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
void poi_permutation(int*, int, int, double*, double[][p]);
void swap(int*, int*);

int main( ) {
    double poi_map[p][p] = {{0}};
    double minDistance   = 9999999;
    int poi_index[p]    = {0};

    for (size_t o_iter = 0; o_iter < p; o_iter++)
        for (size_t i_iter = 0; i_iter < p; i_iter++) poi_map[o_iter][i_iter] = v_distance(poi_twd97tm2[o_iter], poi_twd97tm2[i_iter]);

    for (size_t iter = 0; iter < p; iter++) poi_index[iter] = iter;

    /*for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) std::cout << fixed << setprecision(3) << poi_map[i][j] << "\t";
        std::cout << std::endl;
    }*/

    poi_permutation(poi_index, 0, p - 1, &minDistance, poi_map);

    printf("minDistance of tsp is %lf m", minDistance);
}
void poi_permutation(int poi_index[], int a, int b, double* minDistance, double map[][p]) {
    if (a == b) {
        double tmpDistance = 0;
        for (size_t iter = 0; iter < p - 1; iter++) {
            //printf("%d %lf\t", poi_index[iter],tmpDistance);
            tmpDistance += map[poi_index[iter]][poi_index[iter + 1]];
        }
        tmpDistance += map[poi_index[0]][(poi_index[p-1])];
        //printf("%d \n%lf", poi_index[p-1],tmpDistance);
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
    int temp = *a;
    *a       = *b;
    *b       = temp;
}