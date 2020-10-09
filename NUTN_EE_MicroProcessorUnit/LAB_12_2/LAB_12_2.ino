#include<dht11.h>
#include<math.h>

#define DHT11PIN 20

byte seven_seg_digits[10][7]={
  {0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1},
  {0,0,1,0,0,1,0},
  {0,0,0,0,1,1,0},
  {1,0,0,1,1,0,0},
  {0,1,0,0,1,0,0},
  {0,1,0,0,0,0,0},
  {0,0,0,1,1,1,1},
  {0,0,0,0,0,0,0},
  {0,0,0,1,1,0,0}
  };

dht11 DHT11;

void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<=9;i++)
    pinMode(i, OUTPUT);

  writeDot(1);

  pinMode(A13, OUTPUT);
  digitalWrite(A13, LOW);

  for(int i=30;i<=32;i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  Serial.begin(9600);
  Serial.println("test");
}

void writeDot(byte dot){
  digitalWrite(9, dot);
}

void sevenSegWrite(byte digit){
  byte pin = 2;
  for(byte segCount = 0;segCount<7;segCount++){
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    pin++;
  }
}

void pickDigit(int x){
  digitalWrite(30, 1);
  digitalWrite(31, 1);
  digitalWrite(32, 1);

  switch(x){
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

int d=0;
int Dt, Dtt;

void loop() {
  // put your main code here, to run repeatedly:
  
  if(d>200){
    DHT11.read(DHT11PIN);
    Dt = (float)DHT11.temperature * 100;
    d=0;
  }
  Dtt = Dt;
  int a[4];
  a[0] = (int)Dtt/1000, Dtt-=a[0]*1000;
  a[1] = (int)Dtt/100, Dtt-=a[1]*100;
  a[2] = (int)Dtt/10, Dtt-=a[2]*10;
  a[3] = (int)Dtt/1, Dtt-=a[3]*1;

  
  for(int i=0;i<4;i++){
    delay(4);
    pickDigit(4-i);
    //Serial.println(pow(10, 4-i));
    //int ans = (Dt%(int)pow(10, 4-i)-Dt/(int)pow(10, 3-i))/(int)pow(10, 3-i);
    //int ans = 2;
    sevenSegWrite(a[i]);
    Serial.println(a[i]);
    if(i == 1)
      writeDot(0);
    else
      writeDot(1);
  }
  d++;
}