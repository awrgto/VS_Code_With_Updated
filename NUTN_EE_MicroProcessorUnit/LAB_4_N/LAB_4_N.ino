int rPin = 44, gPin = 45, bPin = 46;

void setup() {
    pinMode(rPin, OUTPUT);    
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
}

void loop() {
    analogWrite(rPin, 100);
    analogWrite(gPin, 0);
    analogWrite(bPin, 100);
    delay(10000);
}