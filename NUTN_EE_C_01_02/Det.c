#include<stdio.h>

int main(){
    int arr[3][3] = {0};
    puts("輸入九個數來當行列式值 ");
    for( size_t count = 0; count < 9; count ++)
        scanf("%d", &arr[count / 3][count % 3]);
    
    for( size_t count = 0; count < 9; count ++)
        printf("%s%4d%4s", count % 3 == 0 ? "|" : "", arr[count / 3][count % 3],  count % 3 == 2 ? "|\n" : "");

    int x = 0, y = 0, z = 0;
    x = arr[0][0] * (arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1]);
    y = arr[1][0] * (arr[0][1] * arr[2][2] - arr[0][2] * arr[2][1]);
    z = arr[2][0] * (arr[0][1] * arr[1][2] - arr[0][2] * arr[1][1]);
    printf("Det : %d", x - y + z);
}
