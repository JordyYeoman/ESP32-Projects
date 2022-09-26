#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/** The clock select pin for the SD card module */
int CS_PIN = 5;
int LED_BUILTIN = 2;
// Analog Input pin for ECG
int ecg_analog_pin = 34;
int ecg_lo_pos = 26;
int ecg_lo_neg = 27;
int arraySize = 3; // Should be the number passed to the array below length
int currentLoopIndex = 0;
int firstPass[3] = {}; // 10 seems to be a good average of filtering to help with noise
int currentAvg = 1;
int loopCount;

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
    currentAvg = localAvg;
    // std::cout << "AVERAGE: " << localAvg << std::endl;
    Serial.println(localAvg);
    // Then clean the array
    std::fill_n(firstPass, arraySize, 0);
    if(currentLoopIndex == arraySize) {
      currentLoopIndex = 0;
    }
  }
};

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode(26, INPUT); // Setup for leads off detection LO +
  pinMode(27, INPUT); // Setup for leads off detection LO -
  // Serial.begin(9600);
  Serial.begin(115200);
  while (!Serial) { }

  // Check the module is connected
  if (!SD.begin(CS_PIN)) {
    Serial.println("Error, SD Initialization Failed");
    return;
  }

  File testFile = SD.open("/SDTest.txt", FILE_WRITE);
  if (testFile) {
    testFile.println("Hello ESP32 SD");
    testFile.println("No way you cheeky dawg");
    testFile.println("Absolutely send this shit");
    testFile.close();
    Serial.println("Success, data written to SDTest.txt");
  } else {
    Serial.println("Error, couldn't not open SDTest.txt");
  }
}

void loop() {
  // Add basic program to show esp32 still functioning correctly
  digitalWrite(LED_BUILTIN, HIGH);
  // Serial.println("LED PULLED HIGH");

  if((digitalRead(ecg_lo_pos) == 1)||(digitalRead(ecg_lo_neg) == 1)){
    Serial.println('!');
    return;
  }
  // Batch data 
  int newInput = analogRead(ecg_analog_pin);
  assignNewDataPoint(newInput);

  File testFile = SD.open("/IRONHEART_BETA.txt", FILE_APPEND);
  if(testFile) {
    if(loopCount > 100) {
      loopCount = 0;
      testFile.println("");
      Serial.println("");
    }
    Serial.print(currentAvg);
    Serial.print(',');
    testFile.print(currentAvg);
    testFile.print(',');
    testFile.close();
  }
  digitalWrite(LED_BUILTIN, LOW);
  // Serial.println("LED PULLED LOW");
  loopCount++;
  delay(5);
}