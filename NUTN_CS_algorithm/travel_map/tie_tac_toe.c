#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char O = 'O', X = 'X', EMPTY = ' ', NO_RESULT = 'N', TIE = 'T';

char winner(char t[3][3]);
void computer_turn(char t[3][3],int * ,int *);

int main(){
    srand((unsigned)time(NULL));
    char table[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int x, y, turn = 1;
    while( 1){
        printf("%s", turn % 2 ? "\nplease enter the position --> " : "computer's position --> ");
        if(turn % 2){ 
            scanf("%d%d", &x, &y);
            fflush(stdin);
            if( x > 3 || x < 0 || y > 3 || y < 0 || table[x][y] != EMPTY) continue;    
        }else computer_turn(table, &x, &y);
        table[x][y] = (turn % 2) ? 'O' : 'X';
		for (int i = 0; i < 3;i ++) printf(" %c | %c | %c \n%s", table[i][0], table[i][1], table[i][2], i != 2 ? "-----------\n" : "");
        if (winner(table) != NO_RESULT) {
            printf("winner is %s !",winner(table) == O ? "player" : winner(table) == TIE ? "both" : "computer");
            break;
        }
        turn ++;
    }
}

char winner(char t[3][3]){
    int com[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} },k = 0;
    for (int i = 0; i < 8; i ++)
        if (t[com[i][0] / 3][com[i][0] % 3] == t[com[i][1] / 3][com[i][1] % 3] && t[com[i][0] / 3][com[i][0] % 3] == t[com[i][2] / 3][com[i][2] % 3] &&  t[ com[ i][ 0] / 3][ com[ i][ 0] % 3] != EMPTY)
            return t[com[i][0] / 3][com[i][0] % 3];     // if any winning row has three values that are the same (and not EMPTY), 
    for (int i = 0; i < 9;i ++)
        k += t[i / 3][i % 3] == EMPTY;                  // since nobody has won, check for a tie (no empty squares left) 
    if( k > 0)
        return NO_RESULT;
    return TIE;
}

void computer_turn( char t[3][3],int *x,int *y){
    int found = 0;
    while( t[found / 3][found % 3] != EMPTY)
        found = rand() % 9;
    *x = found / 3;
    *y = found % 3;
    printf(" %d, %d\n", *x , *y);
}