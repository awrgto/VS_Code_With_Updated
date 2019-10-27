#include <stdio.h>

int enQueue ( int), deQueue ( int *, int *),  empty (), size ();
void printQueue ();

int queue[5], front = 0, rear = 0;

int main(){
    int input = 0, a, b;
    while( input != 5){
        printf("%s","\n1.EnQueue\n2.DeQueue\n3.PrintQueue\n4.Size\n5.End --> ");
        scanf("%d", &input);
        switch( input){
            default :{
                puts("number u send is'nt allowed!");
                break;
            }case 1 :{
                printf("%s","Enter the element u'r wan'na store -->");
                scanf("%d", &a);
                printf("%s\n", enQueue( a) ? "Succeed!" : "Full !!");
                break;
            }case 2 :{
                if ( deQueue( &a, &b))
                    printf("the element u'r delete is %d ( index : %d )\n", a, b);
                else 
                    puts("The queue is empty.");
                break;
            }case 3 :{
                printf("front : %d\nrear : %d\nprint:\n\t", front % 5, rear % 5);
                printQueue();
                break;
            }case 4 :{
                printf("The queue's size is %d\n", size());
                break;
            }case 5 :{
                puts("Bye!");
            }
        }
    }
}
int enQueue (int a){
    if( rear %5 != front % 5 || empty()){
        queue[( rear ++) % 5] = a;
        return 1;
    }return 0;
}
int deQueue (int *a, int *b){
    if( !empty()){
        *b = front % 5;
        *a = queue[(front ++) % 5];
        return 1;
    }return 0;
}
int empty (){ return front == rear ? 1 : 0;}
int size (){ return rear - front;}
void printQueue (){
    if( empty()) puts("The queue is empty.\n");
    else
        for (int iterator = front; iterator < rear; iterator ++)
            printf( "%d\t%s", queue[ iterator % 5],iterator == rear ? "\n" : "");
}