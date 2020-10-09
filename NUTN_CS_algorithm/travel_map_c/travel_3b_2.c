#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define p 12

enum bool { False,
            True };

typedef struct point_of_interest {
    double x;
    double y;
} POI;

typedef struct POI_of_node {
    POI Point;
    struct POI_of_node* next;
    struct POI_of_node* prev;
} POIN;

typedef POIN* POIN_Ptr;
typedef struct POI_of_list {
    POIN_Ptr head;
    POIN_Ptr tail;
    int number_of_menber;
    int (*isEmpty)(struct POI_of_list*);
    int (*push_back)(struct POI_of_list*, POI);
    void (*print)(struct POI_of_list*);
    void (*bsorted)(struct POI_of_list*, int (*compare)(const void*, const void*));
} POIL;

static int isEmpty_impl(POIL* this) { return this->number_of_menber == 0; };
static int push_back_impl(POIL* this, POI data);
static void print_impl(POIL* this);
static void bubble_sorted_impl(POIL*, int (*compare)(const void*, const void*));
static int comp_poi(const void* a, const void* b) { return (((POI*) a)->x < ((POI*) b)->x) || (((POI*) a)->x == ((POI*) b)->x && ((POI*) a)->y < ((POI*) b)->y) ? 0 : 1; };
void swap_POIN(POIN_Ptr a, POIN_Ptr b);
double cross(POI o, POI a, POI b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); };
POIN_Ptr init_POIN(POI data);
POIL* init_POIL( );

int main( ) {
    FILE* inputFile         = fopen("POIs_twd97tm2", "r");
    POIL* poi_input         = init_POIL( );
    POIL* convex_hull_point = init_POIL( );
    POI temp4input          = {0, 0};
    int p_countdown         = p;
    if (inputFile == NULL) return -99;
    while (fscanf(inputFile, "%lf %lf", &(temp4input.x), &(temp4input.y)) != EOF && p_countdown--) poi_input->push_back(poi_input, temp4input);
    //poi_input->print(poi_input);
    poi_input->bsorted(poi_input, comp_poi);
    //poi_input->print(poi_input);
    for (size_t iter = 0; iter < p; iter++) {  // l Convex Hull
        while (convex_hull_point->number_of_menber >= 2 && cross(((convex_hull_point->tail->prev->prev)->front( )), ch.back( ).front( ), *iter) <= 0) ch.pop_back( );
        ch.push_back(std::vector< Point >( ));
        ch.back( ).push_back(*iter);
    }
    int lowwerRecorder = ch.size( ) + 1;

    for (std::vector< Point >::reverse_iterator r_iter = poi.rbegin( ); r_iter != poi.rend( ); r_iter++) {  // will reCount start point for cal area
        while (ch.size( ) >= lowwerRecorder && cross(((ch.end( ) - 2)->front( )), ch.back( ).front( ), *r_iter) <= 0) ch.pop_back( );
        ch.push_back(std::vector< Point >( ));
        ch.back( ).push_back(*r_iter);
    }
}

POIN_Ptr init_POIN(POI data) {
    POIN_Ptr ptr = calloc(1, (rsize_t) sizeof(*ptr));
    ptr->Point   = data;
    ptr->next    = NULL;
    ptr->prev    = NULL;
    return ptr;
}

POIL* init_POIL( ) {
    POIL* ptr             = calloc(1, (rsize_t) sizeof(*ptr));
    ptr->head             = NULL;
    ptr->tail             = NULL;
    ptr->number_of_menber = 0;
    ptr->isEmpty          = isEmpty_impl;
    ptr->push_back        = push_back_impl;
    ptr->print            = print_impl;
    ptr->bsorted          = bubble_sorted_impl;
    return ptr;
}

static int push_back_impl(POIL* this, POI data) {
    POIN_Ptr ptr = init_POIN(data);
    if (this->isEmpty(this))
        this->head = ptr;
    else {
        this->tail->next = ptr;  // debug
        ptr->prev        = this->tail;
    }
    this->tail = ptr;
    this->number_of_menber++;
    return True;
}
static void print_impl(POIL* this) {
    POIN_Ptr current = this->head;
    if (this->isEmpty(this))
        puts("List is empty!");
    else
        for (; current != NULL; current = current->next) printf("%.4lf %.4lf\n", current->Point.x, current->Point.y);
}
static void bubble_sorted_impl(POIL* this, int (*compare)(const void* a, const void* b)) {
    int swapped, i;
    POIN_Ptr ptr1;
    POIN_Ptr lptr = NULL;

    /* Checking for empty list */
    if (this->head == NULL)
        return;

    do {
        swapped = 0;
        ptr1    = this->head;

        while (ptr1->next != lptr) {
            if (compare(&(ptr1->Point), &(ptr1->next->Point))) {
                swap_POIN(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void swap_POIN(POIN_Ptr a, POIN_Ptr b) {
    POI t    = a->Point;
    a->Point = b->Point;
    b->Point = t;
}
