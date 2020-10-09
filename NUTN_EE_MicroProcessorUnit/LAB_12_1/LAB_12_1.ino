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
void setup( ) {
    // put your setup code here, to run once:
    for (int i = 2; i <= 9; i++)
        pinMode(i, OUTPUT);

    writeDot(1);

    pinMode(A13, OUTPUT);
    digitalWrite(A13, LOW);

    for (int i = 30; i <= 32; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }

    pinMode(33, INPUT_PULLUP);
}

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
int state = 0, pState = 0, clickup = 0, clickdown = 0, click = 0;
int c[4] = {0}, t = 0;
void loop( ) {
    clickup = digitalRead(33);
    if (clickup > clickdown)
        click = 0;
    else
        click = 1;
    state = !click ? !state : state;
    if (pState < state)
        for (int k = 0; k < 4; k++)
            c[k] = 0;
    pState = state;
    if (!state)
        for (int i = 0; i < 4; i++) {
            delay(4);
            pickDigit(4 - i % 4);
            sevenSegWrite(c[i % 4]);
        }
    else {
        if (t > 18) {
            t = 0;
            c[3]++;
        }
        if (c[3] > 9) {
            c[3] = 0;
            c[2]++;
        }
        if (c[2] > 5) {
            c[2] = 0;
            c[1]++;
        }
        if (c[1] > 9) {
            c[1] = 0;
            c[0]++;
        }
        t++;
        for (int i = 0; i < 4; i++) {
            delay(4);
            pickDigit(4 - i % 4);
            sevenSegWrite(c[i % 4]);
        }
    }
    clickdown = clickup;
}