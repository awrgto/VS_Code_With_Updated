#include<stdio.h>
#include<stdlib.h>

typedef struct doubleVariableStack{
    char opr;
    double num;
    struct doubleVariableStack *next; //debug
    struct doubleVariableStack *pre;
} dvs;

typedef dvs *dvsPtr;

struct dvsS{
    int count;
    dvsPtr dvsMark;
    dvsPtr dvsHead;  //debug
} dvSpostF = { 0, NULL, NULL}, dvSwordP = { 0, NULL, NULL}, controller;

double getAnswer(char *), eval();
char *inputString(FILE *, size_t);
const char Nothing = '0', postF = '1', wordP = '2', Number = '3', PMB = '4';
int dvsIsEmpty(), dvsSize(), dvsPop(char *, int *), dvsPeek(char *, int *), wordProcess(char *), in2Postfix(), isWhat(char, char);
const int True = 1, False = 0;
void dvsController(char c), printdvs(), dvsPush(char, int);

void inToPostfix(char* infix, char* postfix) { 
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

int main(){
    printf("%s", "put ur question there --> ");
    char *infix = inputString(stdin, 10);
    printf("%c", wordProcess(infix) == 1 ? 'S' : 'F');
    printdvs();
    //printf("\nans : %.3lf", getAnswer(infix));
}

/*double getAnswer(char * infix){
    wordProcess(infix);
    in2Postfix();
    return eval();
}*/

char *inputString(FILE* fp, size_t size){//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char) * size); //size is start size
    if(!str) return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++] = ch;
        if(len==size){
            str = realloc(str, sizeof(char) * (size += 16));
            if(!str) return str;
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}


int dvsIsEmpty() { return controller.count ? 0 : 1;}
int dvsSize() { return controller.count; }
void dvsController( char c) { controller = c == postF ? dvSpostF : dvSwordP; }
void printdvs() { //debug
    dvsPtr current = controller.dvsHead;
    if( dvsIsEmpty()) puts("List is empty!");
	else
		while(current != NULL){
            if( current ->opr != Nothing) printf("\t%c", current ->opr);
            else printf("\t%.3lf", current ->num);
			current = current -> next;
		}
}
void dvsPush( char c_in, int i_in) {
    dvsPtr ptr = malloc(sizeof(*ptr));
    ptr->num = i_in;
    ptr->opr = c_in;
    
    if( dvsIsEmpty()){
        controller.dvsHead = ptr; //debug
        ptr->pre = NULL;
    }else{
        controller.dvsMark -> next = ptr; //debug
        ptr->pre = controller.dvsMark;
    }
    controller.dvsMark = ptr;
    ptr -> next = NULL; //debug
    controller.count++;
}
int dvsPop( char * c_out, int * i_out) {
    dvsPtr beban = controller.dvsMark;
    if( dvsIsEmpty()) return 0;

    controller.dvsMark = controller.dvsMark->pre;
    *i_out = beban->num;
    *c_out = beban->opr;

    free( beban);
    controller.count --;

    if( dvsIsEmpty()) controller.dvsHead = NULL; //debug
    return 1;
}
int dvsPeek( char * c_out, int * i_out){
    if (dvsIsEmpty()) return 0;
    *i_out = controller.dvsMark->num;
    *c_out = controller.dvsMark->opr;
    return 1;
}

int wordProcess(char * infix){
    size_t tok = 0, isHead = True;
    int tmp = 0, i_last = 0, sign = 0;
    char sTmp[2] = {'\0'}, c_last = 'N';
    dvsController(wordP);
    //printf("%s", infix);//debug
    while(infix[tok] != '\0') {
        isHead = 1 - dvsPeek(&c_last, &i_last);
        switch( infix[tok]) {
            case '+': case '-': 
                if( isHead || (!isWhat(c_last, Number))){
                    sign = (sign == 0) ? 1 : sign;
                    sign *= (infix[tok++] == '+') ? 1 : -1;
                }else{
                    dvsPush(infix[tok++], 0);
                }
                break;
            case '*': case '/': 
                if(((!isWhat(c_last, PMB)) && (!isWhat(c_last, Number)))  || isHead)
                    return False;
                dvsPush(infix[tok++], 0);
                isHead = False;
                break;
            case '(': 
                if( sign != 0){
                    dvsPush(Nothing, sign);
                    dvsPush('*', 0);
                    sign = 0;
                }
                dvsPush(infix[tok++], 0);
                break;
            case ')':
                if(!isWhat(c_last, Number) && c_last != ')')
                    return False;
                dvsPush(infix[tok++], 0);
                isHead = False;
                break;
            case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '0':
                do{
                    sTmp[0] = infix[tok];
                    tmp = tmp * 10 + atoi(sTmp);
                } while (isWhat(infix[++tok], Number) == True);
                dvsPush(Nothing, sign == 0 ? tmp : sign * tmp);
                if(infix[tok] == '(') dvsPush('*', 0);
                tmp = 0;
                sign = 0;
                break;
            default : tok++;
        }
    }
    return 1;
}
int isWhat(char c, char mode){
    char number[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, pmb[] = {'+', '-', '('};
    size_t iter = 0;
    switch(mode){
        case Number :
            while( iter < sizeof(number))
                if( c == number[iter++]) return True;
            return False;
        case PMB:
            while(iter < sizeof(pmb))
                if( c == pmb[iter++]) return True;
            return False;
    }
    return False;
}
