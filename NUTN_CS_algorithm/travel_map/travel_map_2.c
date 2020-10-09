#include <stdio.h>
#include <stdlib.h>

const float initLongitude = 120.1, initLatitude = 22.9, degree2radius = 3.14159265358979f / 180.0f;
const int p = 20;

typedef struct node {
    float x;
    float y;
} Node;

typedef struct linkedListArray {  // linkedList Array
    Node point;
    struct linkedListArray* next;
    struct linkedListArray* prev;
} LLA;

typedef LLA* LLAPtr;
typedef struct LLAHook LLAH;
typedef int (*func_t_in)(LLAH*, Node);
typedef Node (*func_t_out)(LLAH*);
typedef int (*func_t_self)(LLAH*);
typedef LLAPtr (*func_t_target)(LLAH*, Node);
typedef int (*func_t_remove)(LLAH*, LLAPtr);
typedef int (*func_t_insert)(LLAH*, LLAPtr, Node);
typedef int (*func_t_swap)(LLAH*, LLAPtr, LLAPtr);

struct LLAHook {
    int count;
    func_t_in push;
    func_t_out pop, shift, back, front;
    func_t_self size, isEmpty, print, clean;
    func_t_target find;
    func_t_insert insert;
    func_t_remove remove;
    func_t_swap swap;
    LLAPtr end;
    LLAPtr begin;
};

const char Nothing  = '0';  //
const int True      = 1;
const int False     = 0;
const int Stack     = 0;
const int Queue4pos = 1;
const int Queue4in  = 2;

// linkedList Array Method
static int isEmpty_impl(LLAH* self) { return self->count == 0; };   // check LLA is empty or not
static int size_impl(LLAH* self) { return self->count; };           // get size of LLA
static Node front_impl(LLAH* self) { return self->begin->point; };  // show first element
static Node back_impl(LLAH* self) { return self->end->point; };     // show last element
static int push_impl(LLAH*, Node);                                  // insert a element at rear
static Node pop_impl(LLAH*);                                        // delete a element at rear
static Node shift_impl(LLAH*);                                      // delete a element at front
static int print_impl(LLAH*);                                       // debug             //print LLA
static int clean_impl(LLAH*);                                       // make LLA empty
static LLAPtr find_impl(LLAH*, Node);                               //find ele and return ptr
static int remove_impl(LLAH*, LLAPtr);                              //remove ele who are ptr
static int insert_impl(LLAH*, LLAPtr, Node);                        //insert node after ptr
static int swap_impl(LLAH*, LLAPtr, LLAPtr);                        //swap two ele
int init_object(LLAH** self) {                                      // call-by-value
    if (NULL == (*self = calloc(1, sizeof(LLAH)))) return -1;
    (*self)->count   = 0;
    (*self)->push    = push_impl;
    (*self)->pop     = pop_impl;
    (*self)->shift   = shift_impl;
    (*self)->back    = back_impl;
    (*self)->front   = front_impl;
    (*self)->size    = size_impl;
    (*self)->isEmpty = isEmpty_impl;
    (*self)->print   = print_impl;
    (*self)->clean   = clean_impl;
    (*self)->find    = find_impl;
    (*self)->insert  = insert_impl;
    (*self)->remove  = remove_impl;
    (*self)->swap    = swap_impl;
    return 0;
}

int main( ) {
    LLAH* poi = NULL;
    init_object(&poi);
    poi->push(poi, (Node){10, 20});
    poi->push(poi, (Node){10, 21});
    poi->push(poi, (Node){10, 22});
    poi->print(poi);
    poi->pop(poi);
    printf("%f   1   %f", poi->back(poi).x, poi->back(poi).y);
    poi->insert(poi, poi->find(poi, (Node){10, 20}),(Node){107, 281});    
    poi->print(poi);
    poi->swap(poi, poi->find(poi, (Node){10, 20}), poi->find(poi, (Node){10, 21}));
    poi->print(poi);
}

static int print_impl(LLAH* self) {
    LLAPtr current = self->begin;
    if (self->isEmpty(self))
        puts("List is empty!");
    else
        while (current != NULL) {
            printf("%f %f\n", current->point.x, current->point.y);
            current = current->next;
        }
    puts("\nprint end");
    return True;
}
static int push_impl(LLAH* self, Node nod) {  // 113
    LLAPtr ptr = calloc(1, sizeof(*ptr));
    ptr->point = nod;

    if (self->isEmpty(self)) {
        self->begin = ptr;  // debug
        ptr->prev   = NULL;
    }
    else {
        self->end->next = ptr;  // debug
        ptr->prev       = self->end;
    }
    self->end = ptr;
    ptr->next = NULL;  // debug
    self->count++;
    return True;
};
static Node pop_impl(LLAH* self) {
    LLAPtr beban = self->end;
    if (self->isEmpty(self)) return (Node){-1, -1};

    self->end     = self->end->prev;
    Node tempNode = beban->point;
    free(beban);
    self->count--;

    if (self->isEmpty(self))
        self->begin = NULL;  // debug
    else
        self->end->next = NULL;
    return tempNode;
}
static Node shift_impl(LLAH* self) {
    LLAPtr beban = self->begin;
    if (self->isEmpty(self)) return (Node){-1, -1};

    self->begin   = self->begin->next;
    Node tempNode = beban->point;
    free(beban);
    self->count--;

    if (self->isEmpty(self))
        self->end = NULL;  // debug
    else
        self->begin->prev = NULL;
    return tempNode;
}
static int clean_impl(LLAH* self) {
    LLAPtr beban = self->end;
    while (beban) {
        self->end = self->end->prev;
        free(beban);
        beban = self->end;
    }
    self->count = 0;
    self->end   = NULL;
    self->begin = NULL;
}
static LLAPtr find_impl(LLAH* self, Node target) {
    LLAPtr current = self->begin;
    while (current != NULL) {
        if (target.x == current->point.x && target.y == current->point.y) return current;
        current = current->next;
    }
    return current;
}
static int insert_impl(LLAH* self, LLAPtr lp, Node nob) {
    if (self->isEmpty(self) || lp == NULL) return False;
    LLAPtr ptr     = calloc(1, sizeof(*ptr));
    ptr->point     = nob;
    ptr->next      = lp->next;
    ptr->prev      = lp;
    lp->next->prev = ptr;
    lp->next       = ptr;
}
static int remove_impl(LLAH* self, LLAPtr lp) {
    if (self->isEmpty(self) || lp == NULL) return False;
    lp->next->prev = lp->prev;
    lp->prev->next = lp->next;
    free(lp);
};
static int swap_impl(LLAH* self, LLAPtr l1, LLAPtr l2){
    Node temp = l1->point;
    l1->point = l2->point;
    l2->point = temp;
    return True;
};