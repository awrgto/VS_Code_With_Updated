int BASE = 2, BASE1 = 37, key[4] = {0, 1, 1, 0}, cri = 0, state = 1;
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
  cri = 0;
  for (int x = 0; x < 4; x++)
    cri += (key[x] == digitalRead(x + 37)) ? 0 : 1;
  for (int i = BASE; i < BASE + 8; i ++)
    digitalWrite(i, cri);
  digitalWrite( 2, (cri * state ));
  state = state ? 0 : 1;
  delay(1000 / 30);
}
