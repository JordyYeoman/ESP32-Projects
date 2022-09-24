// #include <Arduino.h>
// #include <SPI.h>
// #include <SD.h>

// File myFile;
// /** The clock select pin for the SD card module */
// #define CS_PIN 23

// void setup() {
//   Serial.println("Good Day Sir, Systems Online and Ready!");
//   Serial.begin(9600);
//   Serial.print("Initializing SD card...");
 
//   if (!SD.begin(CS_PIN)) {
//     Serial.println("initialization failed!");
//     while (1);
//   }
//   Serial.println("initialization done.");

//   myFile = SD.open("test.txt", FILE_WRITE);
 
//   // if the file opened okay, write to it:
//   if (myFile) {
//     Serial.print("Writing to test.txt...");
//     myFile.println("testing 1, 2, 3.");
//     // close the file:
//     myFile.close();
//     Serial.println("done.");
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }
 
//   // re-open the file for reading:
//   myFile = SD.open("test.txt");
//   if (myFile) {
//     Serial.println("test.txt:");
 
//     // read from the file until there's nothing else in it:
//     while (myFile.available()) {
//       Serial.write(myFile.read());
//     }
//     // close the file:
//     myFile.close();
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
//   }
// }

// void loop() {
//   // // read the input on analog pin 0:
//   // int sensorValue = analogRead(A0);
//   srand(time(NULL));
//   int mockSensorValue = rand() % 100;

//   // print out the value you read:
//   Serial.println(mockSensorValue);
//   delay(1); // delay in between reads for stability
// }

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-microsd-card-arduino/
  
  This sketch can be found at: Examples > SD(esp32) > SD_Test
*/

// #include <Arduino.h>
// #include <FS.h>
// #include <SD.h>
// #include <SPI.h>

// void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
//   Serial.printf("Listing directory: %s\n", dirname);

//   File root = fs.open(dirname);
//   if(!root){
//     Serial.println("Failed to open directory");
//     return;
//   }
//   if(!root.isDirectory()){
//     Serial.println("Not a directory");
//     return;
//   }

//   File file = root.openNextFile();
//   while(file){
//     if(file.isDirectory()){
//       Serial.print("  DIR : ");
//       Serial.println(file.name());
//       if(levels){
//         listDir(fs, file.name(), levels -1);
//       }
//     } else {
//       Serial.print("  FILE: ");
//       Serial.print(file.name());
//       Serial.print("  SIZE: ");
//       Serial.println(file.size());
//     }
//     file = root.openNextFile();
//   }
// }

// void createDir(fs::FS &fs, const char * path){
//   Serial.printf("Creating Dir: %s\n", path);
//   if(fs.mkdir(path)){
//     Serial.println("Dir created");
//   } else {
//     Serial.println("mkdir failed");
//   }
// }

// void removeDir(fs::FS &fs, const char * path){
//   Serial.printf("Removing Dir: %s\n", path);
//   if(fs.rmdir(path)){
//     Serial.println("Dir removed");
//   } else {
//     Serial.println("rmdir failed");
//   }
// }

// void readFile(fs::FS &fs, const char * path){
//   Serial.printf("Reading file: %s\n", path);

//   File file = fs.open(path);
//   if(!file){
//     Serial.println("Failed to open file for reading");
//     return;
//   }

//   Serial.print("Read from file: ");
//   while(file.available()){
//     Serial.write(file.read());
//   }
//   file.close();
// }

// void writeFile(fs::FS &fs, const char * path, const char * message){
//   Serial.printf("Writing file: %s\n", path);

//   File file = fs.open(path, FILE_WRITE);
//   if(!file){
//     Serial.println("Failed to open file for writing");
//     return;
//   }
//   if(file.print(message)){
//     Serial.println("File written");
//   } else {
//     Serial.println("Write failed");
//   }
//   file.close();
// }

// void appendFile(fs::FS &fs, const char * path, const char * message){
//   Serial.printf("Appending to file: %s\n", path);

//   File file = fs.open(path, FILE_APPEND);
//   if(!file){
//     Serial.println("Failed to open file for appending");
//     return;
//   }
//   if(file.print(message)){
//       Serial.println("Message appended");
//   } else {
//     Serial.println("Append failed");
//   }
//   file.close();
// }

// void renameFile(fs::FS &fs, const char * path1, const char * path2){
//   Serial.printf("Renaming file %s to %s\n", path1, path2);
//   if (fs.rename(path1, path2)) {
//     Serial.println("File renamed");
//   } else {
//     Serial.println("Rename failed");
//   }
// }

// void deleteFile(fs::FS &fs, const char * path){
//   Serial.printf("Deleting file: %s\n", path);
//   if(fs.remove(path)){
//     Serial.println("File deleted");
//   } else {
//     Serial.println("Delete failed");
//   }
// }

// void testFileIO(fs::FS &fs, const char * path){
//   File file = fs.open(path);
//   static uint8_t buf[512];
//   size_t len = 0;
//   uint32_t start = millis();
//   uint32_t end = start;
//   if(file){
//     len = file.size();
//     size_t flen = len;
//     start = millis();
//     while(len){
//       size_t toRead = len;
//       if(toRead > 512){
//         toRead = 512;
//       }
//       file.read(buf, toRead);
//       len -= toRead;
//     }
//     end = millis() - start;
//     Serial.printf("%u bytes read for %u ms\n", flen, end);
//     file.close();
//   } else {
//     Serial.println("Failed to open file for reading");
//   }


//   file = fs.open(path, FILE_WRITE);
//   if(!file){
//     Serial.println("Failed to open file for writing");
//     return;
//   }

//   size_t i;
//   start = millis();
//   for(i=0; i<2048; i++){
//     file.write(buf, 512);
//   }
//   end = millis() - start;
//   Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
//   file.close();
// }

// void setup(){
//   Serial.begin(115200);
//   if(!SD.begin(5)){
//     Serial.println("Card Mount Failed");
//     return;
//   }
//   uint8_t cardType = SD.cardType();

//   if(cardType == CARD_NONE){
//     Serial.println("No SD card attached");
//     return;
//   }

//   Serial.print("SD Card Type: ");
//   if(cardType == CARD_MMC){
//     Serial.println("MMC");
//   } else if(cardType == CARD_SD){
//     Serial.println("SDSC");
//   } else if(cardType == CARD_SDHC){
//     Serial.println("SDHC");
//   } else {
//     Serial.println("UNKNOWN");
//   }

//   uint64_t cardSize = SD.cardSize() / (1024 * 1024);
//   Serial.printf("SD Card Size: %lluMB\n", cardSize);

//   listDir(SD, "/", 0);
//   createDir(SD, "/mydir");
//   listDir(SD, "/", 0);
//   removeDir(SD, "/mydir");
//   listDir(SD, "/", 2);
//   writeFile(SD, "/hello.txt", "Hello ");
//   appendFile(SD, "/hello.txt", "World!\n");
//   readFile(SD, "/hello.txt");
//   deleteFile(SD, "/foo.txt");
//   renameFile(SD, "/hello.txt", "/foo.txt");
//   readFile(SD, "/foo.txt");
//   testFileIO(SD, "/test.txt");
//   Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
//   Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
// }

// void loop(){

// }

/** This program tests the SD card module is working */
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/** The clock select pin for the SD card module */
int CS_PIN = 5;
int LED_BUILTIN = 2;

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  // Initialize the Serial (it'll tell us if the program runned correctly)
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
  Serial.println("LED PULLED HIGH");
  File testFile = SD.open("/SDTest.txt", FILE_WRITE);
  if(testFile) {
    Serial.println("");
    testFile.println("");
    for(int i = 0; i < 10000; i++) {
        testFile.print(i);
        testFile.print(',');
        Serial.print(i);
        Serial.print(',');
        delay(1);
    }
    testFile.close();
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED PULLED LOW");
  delay(10000);
}