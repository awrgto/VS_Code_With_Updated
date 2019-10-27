int  resis = A0, rPin = 44, gPin = 45, bPin = 46;
void setup( ) {
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);

    pinMode(resis, INPUT);
}

void loop( ) {
    analogWrite(rPin, analogRead(resis) / 4);
    analogWrite(gPin, 0);
    analogWrite(bPin, 100);
    delay(10);
}
