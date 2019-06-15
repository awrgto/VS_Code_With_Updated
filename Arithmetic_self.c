#include<stdio.h>
#include<stdlib.h>

typedef struct doubleVariableStruct{
    char opr;
    double num;
    struct doubleVariableStruct *next; 
    struct doubleVariableStruct *pre;
} dvs;

typedef dvs *dvsPtr;

struct dvsHook{
    int count;
    dvsPtr dvsTail;
    dvsPtr dvsHead;
} dvsH[3] = {{0, NULL, NULL}};

char *inputString(FILE *, size_t);
const char Nothing = '0', Number = '3', PMB = '4';
int dvsIsEmpty(int), dvsSize(int), dvsPop(char *, double *, int), dvsPeek(char *, double *, int), dvsDeQueue(char *, double *, int);
int wordProcess(char *), isWhat(char, char), inToPostfix(int, int), oprPriority(char);
const int True = 1, False = 0, Stack = 0, QueuePostfix = 1, QueueInfix = 2;
double eval(int), cal(char, double, double), getAnswer(char *);
void printdvs(int), dvsPush(char, double, int);

int main(){
    printf("%s", "put ur question there --> ");
    char *infix = inputString(stdin, 10);
    printf("\nans : %.3lf", getAnswer(infix));
}

double getAnswer(char * infix){
    size_t check = 2;
    check -= wordProcess(infix);
    //printdvs(QueueInfix); //debug 這將顯示文字分析做了什麼
    check -= inToPostfix(QueueInfix, QueuePostfix);
    //printdvs(QueuePostfix); //debug 這將顯示轉後序程式做了什麼
    if (check) puts("ur input maybe have something wrong!");
    return eval(QueuePostfix);
}

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
int dvsIsEmpty(int controller) { return dvsH[controller].count ? 0 : 1;}
int dvsSize(int controller) { return dvsH[controller].count; }
void printdvs(int controller) { //debug
    dvsPtr current = dvsH[controller].dvsHead;
    if( dvsIsEmpty(controller)) puts("List is empty!");
	else
		while(current != NULL){
            if( current ->opr != Nothing) printf(" %c", current ->opr);
            else printf(" %.3lf", current ->num);
			current = current -> next;
		}
    puts("\nprint end");
}
void dvsPush( char c_in, double d_in, int controller) {
    dvsPtr ptr = malloc(sizeof(*ptr));
    ptr->num = d_in;
    ptr->opr = c_in;
    
    if( dvsIsEmpty(controller)){
        dvsH[controller].dvsHead = ptr; //debug
        ptr->pre = NULL;
    }else{
        dvsH[controller].dvsTail -> next = ptr; //debug
        ptr->pre = dvsH[controller].dvsTail;
    }
    dvsH[controller].dvsTail = ptr;
    ptr -> next = NULL; //debug
    dvsH[controller].count++;
}
int dvsPop( char * c_out, double * d_out, int controller) {
    dvsPtr beban = dvsH[controller].dvsTail;
    if( dvsIsEmpty(controller)) return Flase;

    dvsH[controller].dvsTail = dvsH[controller].dvsTail->pre;
    *d_out = beban->num;
    *c_out = beban->opr;

    free( beban);
    dvsH[controller].count --;

    if( dvsIsEmpty(controller)) dvsH[controller].dvsHead = NULL; //debug
    else dvsH[controller].dvsTail->next = NULL;
    return True;
}
int dvsPeek( char * c_out, double * d_out, int controller){
    if (dvsIsEmpty(controller)) return Flase;
    *d_out = dvsH[controller].dvsTail->num;
    *c_out = dvsH[controller].dvsTail->opr;
    return True;
}
int dvsDeQueue( char * c_out, double * d_out, int controller){
    dvsPtr beban = dvsH[controller].dvsHead;
    if( dvsIsEmpty(controller)) return Flase;

    dvsH[controller].dvsHead = dvsH[controller].dvsHead->next;
    *d_out = beban->num;
    *c_out = beban->opr;

    free( beban);
    dvsH[controller].count --;

    if( dvsIsEmpty(controller)) dvsH[controller].dvsTail = NULL; //debug
    else dvsH[controller].dvsHead->pre = NULL;
    return True;
}
int wordProcess(char * infix){
    size_t tok = 0, isHead = True;
    int tmp = 0,sign = 0;
    double d_last;
    char sTmp[2] = {'\0'}, c_last = 'N';
    //printf("%s", infix);//debug
    while(infix[tok] != '\0') {
        isHead = 1 - dvsPeek(&c_last, &d_last, QueueInfix);
        switch( infix[tok]) {
            case '+': case '-': 
                if( isHead || ((!isWhat(c_last, Number)) && c_last != ')')){
                    sign = (sign == 0) ? 1 : sign;
                    sign *= (infix[tok++] == '+') ? 1 : -1;
                }else{
                    dvsPush(infix[tok++], 0, QueueInfix);
                }
                break;
            case '*': case '/': 
                if(((!isWhat(c_last, Number)) && c_last != ')')  || isHead)
                    return False;
                dvsPush(infix[tok++], 0, QueueInfix);
                isHead = False;
                break;
            case '(': 
                if( sign != 0){
                    dvsPush(Nothing, sign, QueueInfix);
                    dvsPush('*', 0, QueueInfix);
                    sign = 0;
                }
                dvsPush(infix[tok++], 0, QueueInfix);
                break;
            case ')':
                if(!isWhat(c_last, Number) && c_last != ')')
                    return False;
                dvsPush(infix[tok++], 0, QueueInfix);
                isHead = False;
                break;
            case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '0':
                do{
                    sTmp[0] = infix[tok];
                    tmp = tmp * 10 + atoi(sTmp);
                } while (isWhat(infix[++tok], Number) == True);
                dvsPush(Nothing, sign == 0 ? tmp : sign * tmp, QueueInfix);
                if(infix[tok] == '(') dvsPush('*', 0, QueueInfix);
                tmp = 0;
                sign = 0;
                break;
            default : tok++;
        }
    }
    return True;
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
int inToPostfix(int infix, int postfix) {
    char c_infix, c_last, c_pop;
    double d_infix, d_last, i_pop;
    while (dvsDeQueue(&c_infix, &d_infix, infix)) {
        switch (c_infix) {
            case '(':              // 運算子堆疊
                dvsPush(c_infix, d_infix, Stack);
                break; 
            case '+': case '-': case '*': case '/':
                while(!dvsIsEmpty(Stack)) {
                    dvsPeek(&c_last, &d_last, Stack);
                    if(oprPriority(c_last) < oprPriority(c_infix)) break;
                    dvsPop(&c_pop, &i_pop, Stack);
                    dvsPush(c_pop, i_pop, postfix);
                }
                dvsPush(c_infix, d_infix, Stack); // 存入堆疊
                break; 
            case ')': 
                while(!dvsIsEmpty(Stack)) { // 遇 ) 輸出至 (
                    dvsPeek(&c_last, &d_last, Stack);
                    if(c_last == '(') break;
                    dvsPop(&c_pop, &i_pop, Stack);
                    dvsPush(c_pop, i_pop, postfix);
                } 
                dvsPop(&c_pop, &i_pop, Stack);  // 不輸出 ( 
                break; 
            default:  // 運算元直接輸出
                dvsPush(c_infix, d_infix, postfix);
        }
    }
    while(!dvsIsEmpty(Stack)) {
        dvsPop(&c_pop, &i_pop, Stack);
        if(c_pop == '(') return Flase;
        dvsPush(c_pop, i_pop, postfix);
    }
    return True;
} 
int oprPriority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 
double eval(int postfix) {  
    char c_infix, c_pop1, c_pop2;
    double d_infix, i_pop1, i_pop2;
    while (dvsDeQueue(&c_infix, &d_infix, postfix)) {
        switch (c_infix) {
            case '+': case '-': case '*': case '/':
                dvsPop(&c_pop1, &i_pop1, Stack);
                dvsPop(&c_pop2, &i_pop2, Stack);
                dvsPush(Nothing, cal(c_infix, i_pop2, i_pop1), Stack);
                break; 
            default: 
                dvsPush(Nothing, d_infix, Stack);
        }
    }          
    dvsPop(&c_pop1, &i_pop1, Stack); 
    return i_pop1;
}
double cal(char opr, double pop2, double pop1) { 
    switch(opr) { 
        case '+': return pop2 + pop1; 
        case '-': return pop2 - pop1; 
        case '*': return pop2 * pop1; 
        case '/': return pop2 / pop1; 
    }
    return False;
}