// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <espnow.h>

// // //---- MASTER ----//

// int LED = 2;

// // Structure example to send data
// // Must match the receiver structure
// typedef struct struct_message
// {
//   char a[32];
//   int b;
//   float c;
//   String d;
//   bool e;
// } struct_message;

// // For initial setup, add to loop method and continously call
// // Serial.print("ESP8266 Board MAC Address:  ");
// // Serial.println(WiFi.macAddress());

// // Master

// // REPLACE WITH RECEIVER MAC Address
// uint8_t broadcastAddress[] = {0xCC, 0x50, 0xE3, 0x6E, 0xC0, 0x92};
// // Create a struct_message called sentData
// struct_message sentData;

// unsigned long lastTime = 0;
// unsigned long timerDelay = 5; // send readings timer in ms

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
//   // Serial.print("ESP8266 Board MAC Address:  ");
//   // Serial.println(WiFi.macAddress());

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
// float infaredVal = 0.0f;

// void loop()
// {
//   Serial.println("Infared Sensor Reading");
//   Serial.print(infaredVal);
//   Serial.println("");

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
//     strcpy(sentData.a, "THIS IS A CHAR");
//     sentData.b = remoteLedStatus; // random(1, 20);
//     sentData.c = 6.43;
//     sentData.d = "Hello";
//     sentData.e = false;

//     // Send message via ESP-NOW
//     esp_now_send(broadcastAddress, (uint8_t *)&sentData, sizeof(sentData));

//     lastTime = millis();
//   }
//   digitalWrite(LED, HIGH);
//   delay(250);
// }