#include <stdio.h>
#include <stdlib.h>

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

int main(void){
    char *m;

    printf("input string : ");
    m = inputString(stdin, 10);
    printf("%s\n", m);

    char *n = stringProcess( m);
    
    printf("%s\n", n);

    free(m);
    return 0;
}