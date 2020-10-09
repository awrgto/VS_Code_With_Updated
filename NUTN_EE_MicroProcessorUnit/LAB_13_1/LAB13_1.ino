//#include<stepper.h>
#define A 2
#define B 3
#define A_BAR 4
#define B_BAR 5
#define tt 2
unsigned run2_F[8][2] = {{A,0},{A,B},{B,0},{B,A_BAR},{A_BAR,0},{A_BAR,B_BAR},{B_BAR,0},{B_BAR,A}};

void stop1( ) {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(A_BAR, LOW);
    digitalWrite(B_BAR, LOW);
}
void setup( ) {
    int i;
    for (i = 2; i < 6; i++)
        pinMode(i, OUTPUT);
}
void loop(){
    int i,j;
    for (i = 0; i < 4; i++){
        stop1();
        digitalWrite(run2_F[i*2][0],HIGH);
        delayMicroseconds(14400);

        stop1();
        for (j = 0; j < 2; j++)
            digitalWrite(run2_F[i*2+1][j],HIGH);
        delayMicroseconds(14400);
    }
}