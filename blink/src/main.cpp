#include <Arduino.h>
#include <iostream>

const int switchDelay = 250;
int ledsArr[6] = { 12, 14, 33, 32, 4, 19 };
size_t LengthOfArray = sizeof ledsArr / sizeof ledsArr[0];

void setup() {
  Serial.begin(115200);
  for(int i = 0; i < LengthOfArray; i++) {
    pinMode(ledsArr[i], OUTPUT);
  }
}

void loop() {
  // for(int i = 0; i <= LengthOfArray; i++) {
  //   digitalWrite(ledsArr[i], HIGH);
  //   digitalWrite(ledsArr[i - 1], LOW);
  //   delay(switchDelay);
  // };
  // Loop through leds then loop backwards through leds to create the effect of a bounce
  for(int i = 0; i <= LengthOfArray; i++) {
    bool flag = false;
    if(i == LengthOfArray){
      for(int k = LengthOfArray; k >= 0; k--) {
        if(k == 0) return;
        digitalWrite(ledsArr[k], HIGH);
        if(k != LengthOfArray) {
          digitalWrite(ledsArr[k + 1], LOW);
          delay(switchDelay);
        }
      }
    }
    std::cout << "Current i value:: " << i << std::endl;
    digitalWrite(ledsArr[i], HIGH);
    digitalWrite(ledsArr[i - 1], LOW);
    delay(switchDelay);
  };
}