#include <stdio.h>

char O = 'O', X = 'X', EMPTY = ' ', NO_RESULT = 'N', TIE = 'T';

char winner(char t[3][3]);
void computer_turn(char t[3][3],int * ,int *);
int next_win(char t[3][3], char mark);

int main(){
    char table[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int x, y, turn = 1;
    printf("%s","Do you need to first? Yes(1),No(2)");
    scanf("%d", &turn);
    fflush(stdin);
    while( 1){
        printf("%s", turn % 2 ? "\nplease enter the position --> " : "computer's position -->");
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

int next_win(char t[3][3],char mark){
    for (int move = 0,found = 0; move < 9;move ++){
        if (t[move / 3][move % 3] == EMPTY) { 
            t[move / 3][move % 3] = mark;       //try move
            found = winner(t) == mark;          //test for winner
            t[move / 3][move % 3] = EMPTY;      //undo move
        }if (found == 1) return move + 1;
    } 
    return 0;
}

void computer_turn( char t[3][3],int *x,int *y){
    int found = next_win(t, X);     //if computer can win on next move, that is  the move to make

    if (found == 0)             
        found = next_win(t, O);     //otherwise, if opponent can win on next move, that's the move to make

    if (found == 0) {               //otherwise, moving to the best open square is the move to make 
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        for (int i = 0; found == 0 && i < 9; i++)
            if (t[BEST_MOVES[i] / 3][BEST_MOVES[i] % 3] == EMPTY)
                found = BEST_MOVES[i] + 1;
    }
    *x = (found - 1) / 3;
    *y = (found - 1) % 3;
    printf(" %d, %d\n", *x , *y);
}