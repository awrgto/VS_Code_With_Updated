#include <stdio.h>

int push (int), pop (int *), empty (), size ();
void printStack ();

int stack[5], pin = 0;

int main(){
    int input = 0, a;
    while( input != 5){
        printf("%s","\n1.Push\n2.Pop\n3.PrintStack\n4.Empty?\n5.End --> ");
        scanf("%d", &input);
        switch( input){
            default :{
                puts("number u send is'nt allowed!");
                break;
            }case 1 :{
                printf("%s","Enter the element u'r wan'na store -->");
                scanf("%d", &a);
                printf("%s\n", push( a) ? "Succeed!" : "Full !!");
                break;
            }case 2 :{
                if ( pop( &a))
                    printf("the element u'r delete is %d\n",a);
                else 
                    puts("The stack is empty.");
                break;
            }case 3 :{
                printStack();
                break;
            }case 4 :{
                printf("The stack is%s empty.", empty() ? "" : "n't");
                break;
            }case 5 :{
                puts("Bye!");
            }
        }
    }
}
int push (int a){
    if( pin < 5){
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