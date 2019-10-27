#include <stdio.h>
#define NUMBER 5 

int push (int), pop (int *), empty (), size ();
void printStack ();

int stack[ NUMBER], pin = 0;

int main(){
    int input = 0, a;
    printf("%s","The Dec number --> ");
    scanf("%d", &input);
    while(input > 0){
        push( input % 16);
        input /= 16;
    }
    printf("%s","The Hex number --> ");
    while( pop( &a))
        printf("%c", a > 9 ? 'A' + a - 10: '0' + a);
}
int push (int a){
    if( pin < NUMBER){
        stack[ pin ++] = a;
        return 1;
    }return 0;
}
int pop (int *a){
    if( !empty()){
        *a = stack[ -- pin];
        return 1;
    }return 0;
}
int empty (){ return pin ? 0 : 1;}
int size (){ return pin;}
void printStack (){
    if( empty()) puts("The stack is empty.\n");
    else
        for (int iterator = 0; iterator < pin; iterator ++)
            printf( "%d\t%s", stack[ iterator],iterator == pin ? "\n" : "");
}