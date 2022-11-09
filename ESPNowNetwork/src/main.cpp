#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

int LED = 2;

// For initial setup, add to loop() method and continously call
// Serial.print("ESP8266 Board MAC Address:  ");
// Serial.println(WiFi.macAddress());

// Master

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xCC, 0x50, 0xE3, 0x6E, 0xC0, 0x92};
// Slave address = CC:50:E3:6E:C0:92

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

// Create a struct_message called myData
struct_message myData;

// unsigned long lastTime = 0;
// unsigned long timerDelay = 500; // send readings timer

// // Callback when data is sent
// void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus)
// {
//   Serial.print("Last Packet Send Status: ");
//   Serial.println(sendStatus);
//   if (sendStatus == 0)
//   {
//     Serial.println("Delivery success");
//   }
//   else
//   {
//     Serial.println("Delivery fail");
//   }
// }

// void setup()
// {
//   Serial.begin(115200);
//   pinMode(LED, OUTPUT);
//   // Set device as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);
//   Serial.print("ESP8266 Board MAC Address:  ");
//   Serial.println(WiFi.macAddress());

//   // Init ESP-NOW
//   if (esp_now_init() != 0)
//   {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }

//   // Once ESPNow is successfully Init, we will register for Send CB to
//   // get the status of Trasnmitted packet
//   esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
//   esp_now_register_send_cb(OnDataSent);

//   // Register peer
//   esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
// }

// bool val = false;

// void loop()
// {
//   delay(1000);            // wait for 1 second.
//   digitalWrite(LED, LOW); // turn the LED on.
//   int remoteLedStatus = 0;
//   if (val)
//   {
//     remoteLedStatus = 1;
//     val = false;
//   }
//   else
//   {
//     remoteLedStatus = 0;
//     val = true;
//   }
//   Serial.println(" ");
//   Serial.println("Remote Led Status: ");
//   Serial.print(remoteLedStatus);
//   Serial.println(" ");
//   if ((millis() - lastTime) > timerDelay)
//   {
//     // Set values to send
//     strcpy(myData.a, "THIS IS A CHAR");
//     myData.b = remoteLedStatus; // random(1, 20);
//     myData.c = 6.43;
//     myData.d = "Hello";
//     myData.e = false;

//     // Send message via ESP-NOW
//     esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

//     lastTime = millis();
//   }
//   delay(1000); // wait for 1 second.
//   digitalWrite(LED, HIGH);
// }

//
//
//
//
//
//
//
//
//
//
//
//
//
// --- SLAVE ---
//
//

// Global variable to store state
int ledVal = 0;
// Callback function that will be executed when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len)
{
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  ledVal = myData.b;
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("String: ");
  Serial.println(myData.d);
  Serial.print("Bool: ");
  Serial.println(myData.e);
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
  delay(500);
  Serial.println("Loop Ending");
  Serial.println("-------------");
  delay(500);
}