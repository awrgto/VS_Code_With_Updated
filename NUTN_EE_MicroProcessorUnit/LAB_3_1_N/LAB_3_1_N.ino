int BASE = 2, BASE1 = 37, state = 1;
void setup() {
  for (int i = 0; i < 4; i ++) {
    pinMode(i + BASE, OUTPUT);
    pinMode(i + BASE1, INPUT_PULLUP);
  }
  pinMode(A15, OUTPUT);
  digitalWrite(A15, LOW); 
}

void loop(){
  for (int x = 0; x < 4; x++)
    digitalWrite(x + 2, ((digitalRead(x + 37) ? 0 : 1) * state ) ? 0 : 1);
  state = state ? 0 : 1;
  delay(1000/30);
}
