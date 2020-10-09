#include<LiquidCrystal.h>
#include<dht11.h>

LiquidCrystal lcd(49,48,47,43,42,41);
dht11 DHT11;

#define DHT_PIN 20
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
}
int i=0;
void loop() {
  DHT11.read(DHT_PIN);
  // put your main code here, to run repeatedly:
  float f = (float)DHT11.temperature / 5 * 9 + 32;
  
  lcd.setCursor(0,0);
  lcd.print("Humi:      %");
  lcd.setCursor(5,0);
  lcd.print((float)DHT11.humidity, 2);
  if(i){
    lcd.setCursor(0,1);
    lcd.print("Temp:      oF");
    lcd.setCursor(5,1);
    lcd.print(f, 2);
  }
  else{
    lcd.setCursor(0,1);
    lcd.print("Temp:      oC");
    lcd.setCursor(5,1);
    lcd.print((float)DHT11.temperature, 2);
  }
  i = !i;
  delay(1000);
}

