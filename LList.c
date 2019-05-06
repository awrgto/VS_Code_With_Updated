#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef Node *NodePtr;

int size (), empty (), insert ( NodePtr), deleteNode ( int), exist ( int), numberOfList = 0;
NodePtr first = NULL;
void printList();

int main(){
	setvbuf(stdout,NULL,_IONBF,0);
    int type=0,input=0;
    do{
        printf("%s","\nEnter type\n\t1.size\n\t2.isEempty\n\t3.exist\n\t4.printList\n\t5.insert\n\t6.delete\n\t7.exit : ");
        scanf("%d",&type);
        switch(type){
            default :{
                printf("%s\n","only can choice 1~7,Plz reTry");
                break;
            }case 1:{
                printf("size = %d",size());
                break;
            }case 2:{
                printf("it%s empty\n",empty()?"'s":" isn't");
                break;
            }case 3:{
                printf("%s","input the number u wanna find : ");
                scanf("%d",&input);
                printf("%s\n",exist(input) != 0 ? "it existed":"it dosen't existed");
                break;
            }case 4:{
                printList();
                break;
            }case 5:{
                printf("%s","input yor data : ");
                NodePtr ptr = (NodePtr)malloc(sizeof(Node));
                scanf("%d",&(ptr->data));
                printf("%s\n",insert(ptr)?"succeed!":"This number does existed!");
                break;
            }case 6:{
                printf("%s","input yor wanna del : ");
                scanf("%d", &input);
                printf("%s\n",deleteNode( input)?"succeed!":"it dosen't existed !");
                break;
            }case 7:{
                puts("bye !");
                break;
            }
        }
    }while(type != 7);
}

int empty(){ return numberOfList > 0 ? 0 : 1;}

int size(){ return numberOfList;}

int insert(NodePtr ptr){
    NodePtr current = first, previous = NULL;
	if( numberOfList == 0 || first -> data > ptr -> data){
		ptr -> next = first;
		first = ptr;
	}else{
        while( current != NULL){
            if( current -> data == ptr -> data)
                return 0;
            else if( current -> data > ptr -> data){
                ptr -> next = current;
                previous -> next = ptr; 
                numberOfList ++;
                return 1;
            }else{
                previous = current;
                current = current -> next;
            }
        }
        previous -> next = ptr;
        ptr -> next = NULL;
        printf("%s",previous -> next -> next == NULL ? "Y" : "N");
	}
	numberOfList ++;
	return 1;
}

int exist( int target){
    NodePtr current = first;
    int count = 0;
	while( current != NULL){
		if( current -> data == target)
			return count;
		else
			current=current->next;
        count ++;
	}
	return 0;
}

void printList(){
    NodePtr current = first;
	if(empty())
		printf("List is empty!\n");
	else{
		while(current != NULL){
			printf("\t%3d",current->data);
			current = current->next;
		}
	}
}

int deleteNode(int target){
    NodePtr current = first, goal = first, previous = NULL;
    
	if(empty())
		return 0;
	if( first -> data == target)
		first = first->next;
    else {
        while( current != NULL){
            if( current -> data == target){
                previous -> next = previous -> next -> next;
                goal = current;
                break;
            }else{
                previous = current;
                current = current -> next;
            }
	    }
    }
	free(goal);
	numberOfList--;
	return 1;
}

