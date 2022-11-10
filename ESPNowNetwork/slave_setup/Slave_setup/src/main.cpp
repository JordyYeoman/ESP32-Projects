#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// Global variable to store state
int ledVal = 0;
int LED = 2;

//--- SLAVE ---//

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

// For initial setup, add to loop method and continously call
// Serial.print("ESP8266 Board MAC Address:  ");
// Serial.println(WiFi.macAddress());

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xCC, 0x50, 0xE3, 0x6E, 0xC0, 0x92};
// Create a struct_message called sentData
struct_message sentData;

// Create a struct_message called receivedData
struct_message receivedData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(receivedData.a);
  Serial.print("Int: ");
  ledVal = receivedData.b;
  Serial.println(receivedData.b);
  Serial.print("Float: ");
  Serial.println(receivedData.c);
  Serial.print("String: ");
  Serial.println(receivedData.d);
  Serial.print("Bool: ");
  Serial.println(receivedData.e);
  Serial.println();
}

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  Serial.println("Loop Starting");
  Serial.println("-------------");
  if (ledVal == 0)
  {
    digitalWrite(LED, HIGH); // Turn off LED
  }
  else if (ledVal == 1)
  {
    digitalWrite(LED, LOW); // Turn on LED
  }
  Serial.println("Loop Ending");
  Serial.println("-------------");
  delay(250);
}