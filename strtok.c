#include<stdio.h>
#include<string.h>
int main(){
    char data[] = "confirm,attention,portion,cancellation, reactivate,block,contract,guidance,advice,bulk,purchase,complaint,business,clause,guess,consensus,calculate,profession,suit,arrangement", *tokenPtr = strtok( data, ",");
    int count = 1, appear[26] = {0};
    while(tokenPtr != NULL){
        printf("%d. %s\n", count++, tokenPtr);
        appear[(int)(tokenPtr[0]) - (int)('a')]++;
        tokenPtr = strtok(NULL, ",") ;
    }
    printf("\ninitial a appear %d times.\ninitial b appear %d times.\ninitial c appear %d times.", appear[0], appear[1], appear[2]);
}