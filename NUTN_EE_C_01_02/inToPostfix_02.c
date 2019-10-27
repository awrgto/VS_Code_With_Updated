#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} node;

typedef node *nodePtr;

int size (), empty (),exist ( char, int *), pop ( char *), priority ( char), stackLen = 0;
void printStack (), push ( nodePtr);
char last ();

nodePtr head = NULL, tail = NULL;

int main(){
	//setvbuf( stdout, NULL, _IONBF, 0);
    char infix[50] = "", reward = 'N';
    int i;
    fgets( infix, 49, stdin);
    fflush(stdin);
    for( i = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '+': case '-': case '*': case '/': 
            if(last() == '*' || last() == '/' ) printf("%c", pop( &reward) ? reward : ' ');
            nodePtr ptr = malloc(sizeof(*ptr));
            ptr -> data = infix[i];
            push( ptr); // 存入堆疊
            break; 
        default:  // 運算元直接輸出 
            printf("%c", infix[i]);
    }
    while(size() > 0) printf("%c", pop( &reward) ? reward : ' ');
}

int size(){ return stackLen;}
int empty(){ return head == NULL ? 1 : 0;}
int exist( char target, int * pos){
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
			printf("\t(%d)", current -> data);
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
int pop( char * value){
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
int priority(char a) { 
    if(a == '*' || a == '/') return 2;
    if(a == '+' || a == '-') return 1;
    return 0;
}
char last() { return tail == NULL ? ' ' : tail -> data; }