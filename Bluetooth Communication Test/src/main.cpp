#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void doShit(uint8_t * theSamePayloadBra, size_t length) {
  String message; 
  int msgCharIndex;

 for(int i = 0; i <= length; i++) {
      if((char)theSamePayloadBra[i] == ':' && i != msgCharIndex) {
          msgCharIndex = i + 2; continue; // Plus 2 since the message is ' :"testMsg" '
      }
      if(i == msgCharIndex) {
          char Ltr = (char)theSamePayloadBra[i];
          if(Ltr == '\"') break;
          message += Ltr;
          msgCharIndex += 1;
      }
  }
  Serial.println(" ");
  Serial.println("---MESSAGE---");
  Serial.println(message);
  Serial.println("---MESSAGE---");
  if(message == "on"){
      // Turn onboard led on
      digitalWrite(2, HIGH);
      
  } else {
      // Turn onboard led on
      digitalWrite(2, LOW);
  }
}


class MyCallbacks: public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    uint8_t * value = pCharacteristic->getData();

    if (pCharacteristic->getLength() > 0)
    {
      Serial.println("*********");
      doShit(value, pCharacteristic->getLength());
      // Serial.print("New value: ");
      // for (int i = 0; i < value.length(); i++)
      // {
      //   Serial.print(value[i]);
      // }

      // Serial.println();
      Serial.println("*********");
    }
  }
};

void setup()
{
  Serial.begin(115200);

  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to ESP32-BLE_Server");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");

  BLEDevice::init("ESP32-BLE-Server");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop()
{
  delay(2000);
}