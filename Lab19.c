#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    char name[20];
    int price;
    int weight;
    struct node *next;
} Node;

typedef Node *nodePtr;

nodePtr head = NULL, tail = NULL;

int main(){
    int item, i = 0;
    printf("%s", "背包物品數量 --> ");
    scanf("%d", &item);
    while(item -( i ++)){
        fflush( stdin);
        nodePtr ptr = malloc( sizeof( *ptr));
        printf("物品 %d 為 --> ", i);
        getchar( ); //?
        fgets( ptr -> name, 19, stdin);
        printf("物品 %d 價錢 --> ", i);
        scanf("%d", &( ptr -> price));
        printf("物品 %d 重量 --> ", i);
        scanf("%d", &( ptr -> weight));
        ptr -> next = NULL;
        if( i == 1) head = ptr;
        else tail -> next = ptr;
        tail = ptr;
    }
    nodePtr current = head;
    if(head == NULL) puts("List is empty!");
	else
		while(current != NULL){
			printf("\n址: %p 指向: %p 物品 : %s CP : %.2f", current, current -> next, current -> name, ( float)(current -> price) / current -> weight);
			current = current -> next;
		}
}