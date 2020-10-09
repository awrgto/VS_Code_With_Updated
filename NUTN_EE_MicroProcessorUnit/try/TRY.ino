//#include<stepper.h>
#define A 0
#define B 1
#define A_BAR 2
#define B_BAR 3
#define tt 20
unsigned run2_F[8][2] = {{A,0},{A,B},{B,0},{B,A_BAR},{A_BAR,0},{A_BAR,B_BAR},{B_BAR,0},{B_BAR,A}};

void stop1( ) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(A_BAR, LOW);
    digitalWrite(B_BAR, LOW);
}
void setup( ) {
    int i;
    for (i = 0; i < 4; i++)
        pinMode(i, OUTPUT);
}
void loop(){
    int i,j;
    for (i = 0; i < 4; i++){
        stop1();
        digitalWrite(run2_F[i*2][0],HIGH);
        delay(tt);

        stop1();
        for (j = 0; j < 2; j++)
            digitalWrite(run2_F[i*2+1][j],HIGH);
        delay(tt);
    }
}