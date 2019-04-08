#include <stdio.h>

int main(){
    int prime[26] = {0}, input = 0, primeIndex = 0;
    printf("%s","enter the range -->");
    scanf("%d", &input);

    for(int index = 2; index <= input ; index ++){
        int primeIndexTemp = 0, mark = 0;
        for(; prime[primeIndexTemp] != 0; primeIndexTemp ++){
            if(index % prime[primeIndexTemp] == 0){
                mark = 1;
                break;
            }
        }
        if( mark == 0)
            prime[primeIndex ++] = index;
    }
    printf("total : %d \n", primeIndex);
    for(int index = 0; index < primeIndex; index ++)
        printf("%3d\t%s", prime[index], index % 5 == 4 ? "\n" : "");
    
}