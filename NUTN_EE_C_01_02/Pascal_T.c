#include <stdio.h>

void print(int *);

int main()
{
    int n; //層數
    int i, j; //迴圈用變數
    int table[10] = {0};

    do {
        printf("你要列出幾層？\n > ");
        scanf("%d", &n);
        if(n > 20 || n < 0)
            printf("輸入錯誤，請重新輸入。\n");
    } while(n > 20 || n < 0);
    printf("%d\n",1);
    if(n == 0)
            return 0;
    table[0] = 1;
    print(table);

    for(i = 1; i < n ; ++i)
    {
        for(j = i / 2 + i % 2; j > 0; --j)
        {
            if(table[j] == 0)
                table[j] = table[j - 1] * 2;
            else
                table[j] = table[j] + table[j - 1];
        }
        print(table);
    }
    return 0;
}

void print(int *table)
{
    int i = 0;
    for(; i < 50 && table[i]; ++i)
        printf("%d\t", table[i]);//正序列印

    i -= 1 + (1 - (int)table[1] % 2);//反轉輸出
    i = i < 0? 0: i;

    for(; i >= 0; --i)
        printf("%d\t", table[i]);//倒序列印
    printf("%s","\n");
}