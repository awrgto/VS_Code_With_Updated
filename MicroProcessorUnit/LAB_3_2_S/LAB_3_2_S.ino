int BASE = 2, BASE1 = 33, state = 1;
void setup() {
  for (int i = 0; i < 8; i ++) {
    pinMode(i + BASE, OUTPUT);
    if (i < 4) 
      pinMode(i + BASE1, INPUT_PULLUP);
  }
  pinMode(A15, OUTPUT);
  digitalWrite(A15, LOW); 
}

void loop(){
  digitalWrite(9, ((digitalRead(33) ? 0 : 1) * state) ? 0 : 1);
  digitalWrite(2, ((digitalRead(34) ? 0 : 1) * state) ? 0 : 1);
  if (digitalRead(33) * digitalRead(34))
    for (int x = BASE; x < BASE + 8; x++)
      digitalWrite(x, (digitalRead(35) ? (((digitalRead(36) ? 0 : 1) * state ) ? 0 : 1) : 0));
  state = state ? 0 : 1;
  delay(1000/30);
}
