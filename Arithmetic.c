#include <stdio.h> 
#include <stdlib.h> 

#define MAX 80

char NU = '0',postfixStack = '1', inputStack = '2', *inputString ( FILE*, size_t), *stringProcess( const char*);

typedef struct doubleVariableStack{
    char opr;
    int num;
    struct doubleVariableStack *next;
    struct doubleVariableStack *pre;
} dvs;

typedef dvs *dvsPtr;

struct dvsS{
    int count;
    dvsPtr dvsHead;
    dvsPtr dvsTail;
} dvSpostfix = { 0, NULL, NULL}, dvSeval = { 0, NULL, NULL}, controller;

int dvsPop(int *, char *), dvsSize(), dvsIsEmpty(), priority(char); // 運算子優先;
void dvsPush( int, char), printdvs(), inToPostfix(char*, char*), dvsController( char), reachLimit( char*); // 中序轉後序 
double eval(char*), cal(char, double, double);

int dvsIsEmpty() { return controller.count ? 0 : 1;}
int dvsSize() { return controller.count; }
void dvsController( char c) { controller = c == postfixStack ? dvSpostfix : dvSeval; }
void printdvs() {
    dvsPtr current = controller.dvsHead;
    if( dvsIsEmpty()) puts("List is empty!");
	else
		while(current != NULL){
			printf("\t%d", current ->opr ? current-> opr: current-> num);
			current = current -> next;
		}
}
void dvsPush( int i_in, char c_in) {
    if( !dvsIsEmpty() && controller.dvsTail->opr == NU && c_in == NU){
        controller.dvsTail->num = controller.dvsTail->num * 10 + i_in;
        return;
    }
    dvsPtr ptr = malloc(sizeof(*ptr));
    ptr->num = i_in;
    ptr->opr = c_in;
    
    if( dvsIsEmpty()){
        controller.dvsHead = ptr;
        controller.dvsTail = ptr;
        ptr->pre = NULL;
    }else{
        controller.dvsTail -> next = ptr;
        ptr->pre = controller.dvsTail;
    }
    controller.dvsTail = ptr;
    ptr -> next = NULL;
    controller.count++;
}
int pop( int * i_out, char * c_out) {
    dvsPtr beban = controller.dvsTail;
    if( dvsIsEmpty()) return 0;

    controller.dvsTail = controller.dvsTail->pre;

    *i_out = beban->num;
    *c_out = beban->opr;

    free( beban);
    controller.count --;

    if( !dvsSize()) controller.dvsHead = NULL;

    return 1;
}

int main(void) { 
    char *infix;

    printf("運算式：");
    infix = inputString(stdin, 10);
    printf("%s\n", infix);
    printf("%f", eval(infix));
    
    return 0; 
} 
void inToPostfix(char* infix, char* postfix) { 
    char stack[MAX] = {'\0'};
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '(':              // 運算子堆疊 
            stack[++top] = infix[i]; 
            break; 
        case '+': case '-': case '*': case '/': 
            while(priority(stack[top]) >= priority(infix[i])) { 
                postfix[j++] = stack[top--];
            } 
            stack[++top] = infix[i]; // 存入堆疊 
            break; 
        case ')': 
            while(stack[top] != '(') { // 遇 ) 輸出至 ( 
                postfix[j++] = stack[top--];
            } 
            top--;  // 不輸出 ( 
            break; 
        default:  // 運算元直接輸出 
            postfix[j++] = infix[i];
    }
    while(top > 0) { 
        postfix[j++] = stack[top--];
    }
} 

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 

double eval(char* infix) {
    char postfix[MAX]= {'\0'};
    char opnd[2] = {'\0'};
    double stack[MAX] = {0.0}; 
    
    inToPostfix(infix, postfix);    

    int top, i;
    for(top = 0, i = 0; postfix[i] != '\0'; i++) switch(postfix[i]) { 
        case '+': case '-': case '*': case '/': 
            stack[top - 1] = cal(postfix[i], stack[top - 1], stack[top]); 
            top--; 
            break; 
        default: 
            opnd[0] = postfix[i];
            stack[++top] = atof(opnd);
    }             
    
    return stack[top];
}

double cal(char op, double p1, double p2) { 
    switch(op) { 
        case '+': return p1 + p2; 
        case '-': return p1 - p2; 
        case '*': return p1 * p2; 
        case '/': return p1 / p2; 
    }
    return 0.0f;
}
char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}
char *stringProcess(const char * str){
    size_t reading = 0, len = 0, writting = 0;
    char *res = realloc(NULL, sizeof(char)*10);
    while(str[reading++] != '\0'){
        switch(str[reading]){
            case '-':
                res[writting++] = '-';
                res[writting++] = '1';
                res[writting++] = '*';
                break;
            case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':case '+':case '*':case '/':case '(':case ')':
                res[writting++] = str[reading];
        }
    }
    return res;
}
