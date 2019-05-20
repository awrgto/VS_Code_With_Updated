#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} node;

typedef node *nodePtr;

int size (), empty (),exist ( int, int *), pop ( int *), stackLen = 0;
void printStack (), push ( nodePtr);

nodePtr head = NULL, tail = NULL;

int main(){
	setvbuf( stdout, NULL, _IONBF, 0);
    int type = 0, input = 0, reward = 0;
    while( type != 7){
        printf("%s","\nEnter type\n\t1.push\n\t2.pop\n\t3.printStack\n\t4.empty\n\t5.size\n\t6.exist\n\t7.exit --> ");
        scanf("%d", &type);
        switch( type){
            default :{
                puts("\ntype ERROR ,reTry plz.\n");
                break;
            }case 5:{
                printf("\nsize = %d", size());
                break;
            }case 4:{
                if( !empty()) printf("not empty, size is %d !\n", size());
                else puts("nothing there !");
                break;
            }case 6:{
                printf("\n%s","input the number u wanna find --> ");
                scanf("%d",&input);
                if( exist( input, &reward)) printf("it's exist, on pos %d !\n", reward);
                else puts("not in there !");
                break;
            }case 3:{
                printStack();
                break;
            }case 1:{
                printf("%s","input yor data --> ");
                nodePtr ptr = malloc(sizeof(*ptr));
                scanf("%d",&( ptr -> data));
                push( ptr);
                break;
            }case 2:{
                if(pop( &reward)) printf("%d is deleted !\n", reward);
                else puts("nothing there !");
                break;
            }case 7:{
                puts("bye !");
                break;
            }
        }
    }
}

int size(){ return stackLen;}
int empty(){ return head == NULL ? 1 : 0;}
int exist( int target, int * pos){
    nodePtr current = head;
    *pos = 1;
    while( current != NULL){
        if( current -> data == target) return 1;
        current = current -> next;
        *pos += 1;
    }return 0;
}
void printStack(){
    nodePtr current = head;
    if(empty()) puts("List is empty!");
	else
		while(current != NULL){
			printf("\t%d", current -> data);
			current = current -> next;
		}
}
void push( nodePtr ptr){
    if( head == NULL) head = ptr;
    else tail -> next = ptr;
    tail = ptr;
    ptr -> next = NULL;
    stackLen ++;
}
int pop( int * value){
    nodePtr current = head, previous = NULL;
    if(empty()) return 0;
    *value = tail->data;
    while( current != tail){
        previous = current;
        current = current -> next;
    }
    if( previous == NULL) head = NULL;
    else previous -> next = NULL;
    tail = previous;
    free( current);
    stackLen --;
    return 1;
}