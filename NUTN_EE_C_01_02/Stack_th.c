#include <stdio.h>

int push(int ), pop(int *), exist(int), empty();
void print();

int stack[5] = {0}, index = 0;

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
                print();
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


int empty(){
    return index ? 0 : 1;
}

int push (int a){
    if(index < 5){
        stack[index] = a;
        index++;
        return 1;
    }else
        return 0;
}
int pop(int *a){
    if (index != 0){
        index--;
        *a = stack[index];
        return 1;
    }
    return 0;
}
int exist (int target){
    for (int i = 0; i < index; i++){
        if(target == stack[i])
            return 1;
    }
    return 0;
}
void print(){
    if (index==0)
        puts("stack is empty");
    else{
        for (int i = 0; i < index;i++){
            printf("%d\t", stack[i]);
        }
    }
}