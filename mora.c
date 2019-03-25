#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int result( int, int);
int NPC_roll(void) { return rand() % 3; }

int main(){
    int input = 0, count = 0;
    char sResult[3][11] = {"Player win!","Flat!","NPC win!"}, item[3][10] = {"剪刀","布","石頭"};
    srand(( unsigned) time( NULL));
    while(1){
        printf("%s", "跟電腦猜拳:剪刀(1).布(2).石頭(3)");
        scanf("%d", &input);

        int NPC = NPC_roll(), game = result(input, NPC + 1);
        printf("玩家出%s , 電腦出%s \n----- %s -----\n\n", item[input - 1], item[NPC], sResult[ game]);
        count += game - 1;
        for(int i = -3; i <= 3; i ++)
                if ( i == count ) printf("%s", "  *");
                else printf("%s", "   ");
            printf("%s", "\n -3 -2 -1  0  1  2  3\n\n");
        if ( count == 3){
            printf("%s", "player finaally win!");
            break ;
        }else if(count == -3){
            printf("%s", "Computer finally win!");
            break ;
        }
    }
}

int result(int player, int NPC){
    switch( player - NPC){
        case 0:
            return 1;
        case 1:
        case -2:
            return 0;
        default :
            return 2;
    }
}