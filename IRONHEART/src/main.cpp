#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <vector>

/** The clock select pin for the SD card module */
int CS_PIN = 5;
int LED_BUILTIN = 2;
// Analog Input pin for ECG
int ecg_analog_pin = 34;
int ecg_lo_pos = 26;
int ecg_lo_neg = 27;
int loopCount;
std::vector<std::string> data{};

void setup() {
  Serial.println("Systems Booting...");
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

  File testFile = SD.open("/BootTest.txt", FILE_WRITE);
  if (testFile) {
    testFile.println("Hello ESP32 SD");
    testFile.println("No way you cheeky dawg, absolutely send it!");
    testFile.close();
    Serial.println("Success, data written to SDTest.txt");
  } else {
    Serial.println("Error, couldn't not open SDTest.txt");
  }
}

void loop() {
  // Add basic program to show esp32 still functioning correctly
  digitalWrite(LED_BUILTIN, HIGH);

  // Don't write to SD card if ECG leds are not pulling signal.
  if((digitalRead(ecg_lo_pos) == 1)||(digitalRead(ecg_lo_neg) == 1)){
    Serial.println('!');
    return;
  }

  // Batch data 
  int newInput = analogRead(ecg_analog_pin);
  std::string str = std::to_string(newInput) + ",";
  data.push_back(str);
  if(data.size() >= 100) {
    File testFile = SD.open("/IRONHEART_BETA.txt", FILE_APPEND);
    if(testFile) {
      if(loopCount > 100) {
        loopCount = 0;
        testFile.println("");
        Serial.println("");
      }
      for(int k = 0; k < data.size(); k++) {
        Serial.print(data[k].c_str());
        testFile.print(data[k].c_str());
      }
      testFile.close();
    }
    data.clear();
  }
  digitalWrite(LED_BUILTIN, LOW);
  loopCount++;
  delay(5);
}