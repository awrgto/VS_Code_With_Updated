int BASE = 2;
void setup() {
  pinMode(33, INPUT_PULLUP);
  for (int i = 0; i < 8; i ++){
    pinMode(i + BASE, OUTPUT);
    digitalWrite(i + BASE, 1);
  }
  pinMode(A9, OUTPUT);
  pinMode(A15, OUTPUT);
  digitalWrite(A15, LOW); 
}

void loop(){
  if ( digitalRead( 33) == 0){
    digitalWrite(A9, 1);
    delay(1000);
    digitalWrite(A9, 0);
    for (int i = BASE; i < BASE + 8; i ++)
      digitalWrite(i, 0);
    delay(5000);
    for (int i = BASE; i < BASE + 8; i ++)
      digitalWrite(i, 1);
  }
}
