#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} node;

typedef node *nodePtr;

struct Q {
    int count;
    nodePtr front;
    nodePtr rear;
} qQ = { 0, NULL, NULL};

int size (), empty (),exist ( int, int *), deQueue ( int *);
void printQueue (), enQueue ( nodePtr);

int main(){
    int input = 0, type = 0, a;
    while( type != 7){
        printf("%s","\n1.EnQueue\n2.DeQueue\n3.PrintQueue\n4.empty?\n5.Size\n6.exist?\n7.End --> ");
        scanf("%d", &type);
        switch( type){
            default :{
                puts("number u send is'nt allowed!");
                break;
            }case 1 :{
                printf("%s","Enter the element u'r wan'na store -->");
                nodePtr ptr = malloc(sizeof(*ptr));
                scanf("%d",&( ptr -> data));
                enQueue( ptr);
                break;
            }case 2 :{
                if ( deQueue( &a))
                    printf("the element u'r delete is %d\n", a);
                else 
                    puts("The queue is empty.");
                break;
            }case 3 :{
                printf("print:\n");
                printQueue();
                break;
            }case 4:{
                if( !empty()) printf("not empty, size is %d !\n", size());
                else puts("nothing there !");
                break;
            }case 5 :{
                printf("The queue's size is %d\n", size());
                break;
            }case 6:{
                printf("\n%s","input the number u wanna find --> ");
                scanf("%d",&input);
                if( exist( input, &a)) printf("it's exist, on pos %d !\n", a);
                else puts("not in there !");
                break;
            }case 7 :{
                puts("Bye!");
            }
        }
    }
}
int size() { return qQ.count; }
int empty() { return qQ.count ? 0 : 1; }
void enQueue( nodePtr ptr){
    if( qQ.rear ) qQ.rear->next = ptr;
    if( !qQ.front ) qQ.front = ptr;
    qQ.rear = ptr;
    ptr->next = NULL;
    qQ.count++;
}
int deQueue( int * value){
    nodePtr gost = qQ.front;
    if(empty()) return 0;
    *value = qQ.front -> data;
    qQ.front = qQ.front->next;
    free(gost);
    qQ.count--;
    if( empty()) qQ.rear = NULL;
    return 1;
}
void printQueue(){
    nodePtr current = qQ.front;
    while(current){
        printf("\t%d", current->data);
        if( current == qQ.rear) return;
        current = current->next;
    }
}
int exist(int target, int * pos){
    nodePtr current = qQ.front;
    int c_q = 1;
    while(current){
        if( current ->data == target) {
            *pos = c_q;
            return 1;
        }
        current = current->next;
        c_q++;
    }
    return 0;
}