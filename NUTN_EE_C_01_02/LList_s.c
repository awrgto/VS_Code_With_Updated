#include <stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} node;

typedef node *nodePtr;

int size (), empty (),exist ( int), insert ( nodePtr), delete ( int), ListLen = 0;
void printList ();

nodePtr head = NULL;

int main(){
	setvbuf( stdout, NULL, _IONBF, 0);
    int type = 0, input = 0;
    while( type != 7){
        printf("%s","\nEnter type\n\t1.size\n\t2.isEempty\n\t3.exist\n\t4.printList\n\t5.insert\n\t6.delete\n\t7.exit --> ");
        scanf("%d", &type);
        switch( type){
            default :{
                puts("\ntype ERROR ,reTry plz.\n");
                break;
            }case 1:{
                printf("\nsize = %d", size());
                break;
            }case 2:{
                printf("\nit%s empty\n", empty() ? "'s" : " isn't");
                break;
            }case 3:{
                printf("\n%s","input the number u wanna find --> ");
                scanf("%d",&input);
                printf("\nit%s existed\n",exist(input) != 0 ? "'s" : " isn't");
                break;
            }case 4:{
                printList();
                break;
            }case 5:{
                printf("%s","input yor data --> ");
                nodePtr ptr = malloc(sizeof(*ptr));
                scanf("%d",&( ptr -> data));
                printf("%s\n",insert( ptr) ? "succeed!" : "This number does existed!");
                break;
            }case 6:{
                printf("%s","input yor wanna del : ");
                scanf("%d", &input);
                printf("%s\n",delete( input)?"succeed!":"it dosen't existed !");
                break;
            }case 7:{
                puts("bye !");
                break;
            }
        }
    }
}
int size(){ return ListLen;}
int empty(){ return head == NULL ? 1 : 0;}
int exist( int target){
    nodePtr current = head;
    while( current != NULL){
        if( current -> data == target) return 1;
        else current = current -> next;
    }return 0;
}
void printList(){
    nodePtr current = head;
    if(empty()) puts("List is empty!");
	else
		while(current != NULL){
			printf("\t%d", current -> data);
			current = current -> next;
		}
}
int insert( nodePtr ptr){
    nodePtr current = head, previous = NULL;
    while( current != NULL){
        if( current -> data == ptr -> data) return 0;
        else if( current -> data > ptr -> data) break;
        else{
            previous = current;
            current = current -> next;
        }
    }
    if( previous == NULL){
        ptr -> next = head;
		head = ptr;
    }else{
        ptr -> next = current;
        previous -> next = ptr;
    }
    ListLen ++;
    return 1;
}
int delete( int target){
    nodePtr current = head, previous = NULL;
	if(empty() || !exist( target)) return 0;
	if( head -> data == target) head = head -> next;
    else {
        while( current != NULL){
            if( current -> data == target) break;
            else{
                previous = current;
                current = current -> next;
            }
	    }
        previous -> next = previous -> next -> next;
    }
	free( current);
	ListLen --;
	return 1;
}