#include <LiquidCrystal.h>

int joyPinX = A1;
int joyPinY = A2;
int SW = A3;
int xzero = 0;
int yzero = 0;
int SWstate = 0;
int rPin = 44;
int gPin = 45;
int bPin = 46;

LiquidCrystal lcd(49,48,47,43,42,41);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(SW, INPUT_PULLUP);
  xzero = analogRead(joyPinX);
  yzero = analogRead(joyPinY);
  lcd.begin(16,2);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Pin = ");
  lcd.setCursor(0, 1);
  lcd.print("Light = ");
}

void lcdPrint(int p, int l){
  lcd.setCursor(7, 0);
  lcd.print(p);
  char ch[4];
  sprintf(ch , "%3d", l);
  lcd.setCursor(8, 1);
  lcd.print(ch);
}

int del = 0,delx = 0, cpin = 10000, clight = 0;

void loop() {
  // put your main code here, to run repeatedly:
  
  int x, y, value;
  value = analogRead(joyPinX);
  x = value - xzero;
  value = analogRead(joyPinY);
  y = value - yzero;
  if(del++ > 400 && y > 300){
    cpin += 1;
    del = 0;
  }
  else if(del > 400 && y < -300){
    cpin -= 1;
    del = 0;
  }
  else if((long) y * y < 90000)
    del = 400;

  if(x < -300){
    clight += delx/10;
    if(clight >= 255*20) clight = 255*20;
  }
  else if(x > 300){
    clight -= delx/10;
    if(clight < 0) clight = 0;
  }
  else if((long) x * x < 90000)
    delx = 0;
  delx++;
  lcdPrint(cpin % 3 + 44, clight / 20);

  if(digitalRead(A3) == LOW)
    analogWrite(cpin % 3 + 44, clight / 20);
}


