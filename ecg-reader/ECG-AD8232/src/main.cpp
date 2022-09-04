#include <Arduino.h>
#include <iostream>

// Analog Input pin for ECG
int ecg_analog_pin = 34;
int ecg_lo_pos = 26;
int ecg_lo_neg = 27;
int arraySize = 10; // Should be the number passed to the array below length
int currentLoopIndex = 0;
int firstPass[10] = {}; // 10 seems to be a good average of filtering to help with noise when plugged into mains

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(26, INPUT); // Setup for leads off detection LO +
  pinMode(27, INPUT); // Setup for leads off detection LO -
}

// Helper methods: 
void assignNewDataPoint(int input) {
  // Check if last element in array has been assigned
  if(firstPass[currentLoopIndex] == 0 && currentLoopIndex < arraySize) {
    firstPass[currentLoopIndex] = input;
    currentLoopIndex++;
  } else if (firstPass[arraySize - 1] != 0) {
    // If both first and last elements have been assigned, get the average and print it out
    int sum;
    for(int z = 0; z < sizeof(firstPass)/sizeof(firstPass[0]); z++) {
        sum += firstPass[z];
    }
    int localAvg = sum / arraySize;
    // std::cout << "AVERAGE: " << localAvg << std::endl;
    Serial.println(localAvg);
    // Then clean the array
    std::fill_n(firstPass, arraySize, 0);
    if(currentLoopIndex == arraySize) {
      currentLoopIndex = 0;
    }
  }
};

void loop() {
  if((digitalRead(ecg_lo_pos) == 1)||(digitalRead(ecg_lo_neg) == 1)){
    Serial.println('!');
    return;
  }
  // Batch data 
  int newInput = analogRead(ecg_analog_pin);
  assignNewDataPoint(newInput);
  delay(1);
}