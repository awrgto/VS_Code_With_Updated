#include "pitches.h"
int tune[] = {
    NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_C5,NOTE_B4,NOTE_C5,NOTE_B4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_G5,NOTE_C6,NOTE_B5,NOTE_C6,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_E5,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_E5,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_C5,NOTE_B4,NOTE_C5,NOTE_B4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_G4,NOTE_A4,NOTE_C5,NOTE_A4,NOTE_C5,NOTE_D5,NOTE_D5,NOTE_E5,NOTE_G5,NOTE_C6,NOTE_E5,NOTE_G5,NOTE_C6,NOTE_B5,NOTE_C6,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_A5,NOTE_C6,NOTE_D6,NOTE_E6,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D6,NOTE_A6,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D6,NOTE_E6,NOTE_A5,NOTE_G5,NOTE_C6,NOTE_A5,NOTE_G5,NOTE_B5,NOTE_C6,NOTE_B5,NOTE_A5,NOTE_G5,NOTE_D6,NOTE_E6,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D6,NOTE_E6,NOTE_A5,NOTE_G5,NOTE_A5,NOTE_G5,NOTE_D6,NOTE_E6,NOTE_G6,NOTE_C7,NOTE_B6,NOTE_C7,NOTE_B6,NOTE_A6,NOTE_G6,NOTE_E6
};

short duration[]=
{
    2,2,4,4,4,4,2,2,4,4,4,4,2,2,4,4,4,4,2,4,4,4,4,2,2,2,4,4,4,4,2,2,4,4,4,4,2,2,2,2,4,4,4,4,2,2,2,2,4,4,4,4,2,2,4,4,4,4,2,2,4,4,4,4,2,4,4,4,4,2,2,4,4,2,4,4,2,4,4,4,4,4,4,2,4,4,4,4,2,1,2,2,2,2,4,4,4,4,2,2,4,4,4,4,2,2,4,4,4,4,2,4,4,4,4,2,2,2,4,4,4,4,2,2,4,4,4,4,2,2,2,2,4,4,4,4,2,2,
};
int length;
int tonePin = A9;

void setup()
{
  pinMode(tonePin, OUTPUT);
  length = sizeof(tune)/sizeof(tune[0]);
}

void loop()
{
  for(int x=0;x<length;x++){
    tone(tonePin,tune[x],400/duration[x]-10);
    delay(10);
    noTone(tonePin);
  }
  delay(5000);
}