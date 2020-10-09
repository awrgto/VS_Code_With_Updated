#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define p 12

typedef struct point_of_interest {
    double x;
    double y;
} POI;

const POI poi_twd97tm2[30] = {
    {168499.2522, 2543803.7769},
    {168502.8393, 2544059.6925},
    {168087.6590, 2543364.1322},
    {168818.8743, 2543104.2208},
    {168950.1215, 2542963.5062},
    {169522.5312, 2543034.8114},
    {169769.0516, 2543055.3704},
    {168246.3564, 2544227.3312},
    {163803.1187, 2543189.0074},
    {163528.9189, 2543330.5882},
    {162785.3125, 2543334.8820},
    {162578.6313, 2543546.0903},
    {164069.7493, 2544609.3637},
    {163735.6970, 2544475.6571},
    {163667.7204, 2544897.1218},
    {163866.8951, 2544912.3843},
    {163951.4595, 2544697.5365},
    {164399.6450, 2544786.8476},
    {164263.4921, 2544443.1072},
    {169859.4654, 2544436.2930},
    {169322.3900, 2544687.4339},
    {169221.2709, 2544496.5814},
    {169324.1495, 2544605.3981},
    {169096.8012, 2543237.2597},
    {168950.2768, 2543196.4846},
    {168848.7097, 2543740.6368},
    {163505.5312, 2543663.2336},
    {168424.1674, 2543447.0709},
    {157860.5934, 2561516.1911},
    {160597.5276, 2552055.1702}};

double cross(POI o, POI a, POI b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
double dot(POI o, POI a, POI b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); };
double v_height(POI o, POI a, POI b) { return fabs(cross(o, a, b)) / v_distance(a, o); };
double v_base(POI o, POI a, POI b) { return fabs(dot(o, a, b)) / v_distance(a, o); };
double v_distance(POI a, POI b) { return sqrt(pow((a.x - b.x), 2.0) + pow((a.y - b.y), 2.0)); };
static int comp_poi(const void* a, const void* b) { return (((POI*) a)->x < ((POI*) b)->x) || (((POI*) a)->x == ((POI*) b)->x && ((POI*) a)->y < ((POI*) b)->y) ? -1 : 1; };

int main( ) {
    double poi_map[p][p] = {{0}};
    POI POI_sorted[30]   = {{0, 0}};
    double minDistance   = 99999;
    int poi_index[p]     = {0};

    memcpy(POI_sorted, poi_twd97tm2, (rsize_t) sizeof(poi_twd97tm2));
    qsort(POI_sorted, p, (rsize_t) sizeof(POI), comp_poi);
    //for (int i = 0; i < p; i++) printf("%.4lf\t%.4lf\n", POI_sorted[i].x,POI_sorted[i].y);

}
