//#include<stepper.h>
#define A 2
#define B 3
#define A_BAR 4
#define B_BAR 5
#define tt 75
unsigned run2_F[8][2] = {{A, 0}, {A, B}, {B, 0}, {B, A_BAR}, {A_BAR, 0}, {A_BAR, B_BAR}, {B_BAR, 0}, {B_BAR, A}};

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
    for (int i = 2; i <= 9; i++)
        pinMode(i, OUTPUT);

    writeDot(1);

    pinMode(A13, OUTPUT);
    digitalWrite(A13, LOW);

    for (int i = 30; i <= 32; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
}
int i, j, t = 0;
int a[4] = {0};
void loop( ) {
    t++;
    if (t > 7) {
        t = 0;
        a[0]++;
    }
    if (a[0] > 9) {
        a[0] = 0;
        a[1]++;
    }
    if (a[1] > 9) {
        a[1] = 0;
        a[2]++;
    }
    if (a[2] > 9) {
        a[2] = 0;
        a[3]++;
    }
    for (i = 0; i < 4; i++) {
        stop1( );
        digitalWrite(run2_F[i * 2][0], HIGH);
        for (int i = 0; i < 4; i++) {
            delayMicroseconds(3600);
            pickDigit(1+i);
            sevenSegWrite(a[i]);
        }

        stop1( );
        for (j = 0; j < 2; j++)
            digitalWrite(run2_F[i * 2 + 1][j], HIGH);
        for (int i = 0; i < 4; i++) {
            delayMicroseconds(3600);
            pickDigit(1+i);
            sevenSegWrite(a[i]);
        }
    }
}
byte seven_seg_digits[10][7] = {
    {0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0}};

void writeDot(byte dot) {
    digitalWrite(9, dot);
}

void sevenSegWrite(byte digit) {
    byte pin = 2;
    for (byte segCount = 0; segCount < 7; segCount++) {
        digitalWrite(pin, seven_seg_digits[digit][segCount]);
        pin++;
    }
}

void pickDigit(int x) {
    digitalWrite(30, 1);
    digitalWrite(31, 1);
    digitalWrite(32, 1);

    switch (x) {
        case 1:
            digitalWrite(30, 0);
            digitalWrite(31, 0);
            digitalWrite(32, 0);
            break;
        case 2:
            digitalWrite(30, 1);
            digitalWrite(31, 0);
            digitalWrite(32, 0);
            break;
        case 3:
            digitalWrite(30, 0);
            digitalWrite(31, 1);
            digitalWrite(32, 0);
            break;
        case 4:
            digitalWrite(30, 1);
            digitalWrite(31, 1);
            digitalWrite(32, 0);
            break;
    }
}