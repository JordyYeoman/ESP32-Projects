#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

int ONBOARD_LED = 2;
boolean MONITOR_ECG = false;
BLECharacteristic *pCharacteristic; // Pointing to the address of where our characteristic value is located.

class MyCallbacks: public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic, esp_ble_gatts_cb_param_t* param)
  {
    std::string value = pCharacteristic->getValue();
    String message;

    if (value.length() > 0)
    {
      for (int i = 0; i < value.length(); i++)
      {
        char letter = value[i];
        message += letter;
      }
    }
    Serial.println("MESSAGE: ");
    Serial.print(message);
    if(message == "on") {
      // Turn onboard led on
      digitalWrite(2, HIGH);
      Serial.println("LED ON");
    } 
    if(message == "off") {
      // Turn onboard led off
      digitalWrite(2, LOW);
      MONITOR_ECG = false;
      Serial.println("Systems offline");
    }
    if(message == "system online") {
      MONITOR_ECG = true;
      Serial.print("Systems online and ready sir");
    }
  }
};

// NOTE: - Be sure to use the correct app when communicating, BLE Scanner works well for sending strings/hex messages without chunking the data.
void setup()
{
  // On board led
  pinMode(ONBOARD_LED, OUTPUT);
  Serial.begin(115200);

  BLEDevice::init("ESP32-BLE-Server");
  

  // Define these values outside of setup to give global access
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                          CHARACTERISTIC_UUID,
                                          BLECharacteristic::PROPERTY_READ |
                                          BLECharacteristic::PROPERTY_WRITE |
                                          BLECharacteristic::PROPERTY_NOTIFY
                                        );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Online and ready sir");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void loop()
{
  delay(20);
  // if(MONITOR_ECG) {
    // Batch 'x' amount of responses and then post the average over bluetooth.
    int randomNumber = rand() % 100;
    pCharacteristic->setValue(randomNumber);
    pCharacteristic->notify();
    Serial.println(randomNumber);
  // }
}