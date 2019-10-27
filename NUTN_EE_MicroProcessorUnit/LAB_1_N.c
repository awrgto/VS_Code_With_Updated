int led = 2;
void setup() {
    // put your setup code here, to run once:
    for(int led=2;led<=9;led++){
        pinMode(led, OUTPUT);
        digitalWrite(led,LOW);
    }
    pinMode(A15,OUTPUT);
    digitalWrite(A15,LOW);
    //digitalWrite(4,LOW);
}

void loop() {
    // put your main code here, to run repeatedly:
    for(int led=2;led<=9;led++){
        digitalWrite(led,LOW);
        delay(1000);
        digitalWrite(led,HIGH);
    }
}