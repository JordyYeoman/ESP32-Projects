#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;
/** The clock select pin for the SD card module */
#define CS_PIN 4

void setup() {
  Serial.println("Good Day Sir, Systems Online and Ready!");
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
 
  if (!SD.begin(CS_PIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
 
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
 
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // // read the input on analog pin 0:
  // int sensorValue = analogRead(A0);
  srand(time(NULL));
  int mockSensorValue = rand() % 100;

  // print out the value you read:
  Serial.println(mockSensorValue);
  delay(1); // delay in between reads for stability
}