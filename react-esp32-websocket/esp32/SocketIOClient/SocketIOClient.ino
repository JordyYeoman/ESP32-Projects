
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <Hash.h>

#include <iostream>
#include <string>

ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;

#define USE_SERIAL Serial
#define analogPin A0 

bool led_status = false;
uint8_t * payload;
String inData;
bool endOfMsg;
int messageCharIndex;
int analogInputVal = 0;

void broadcastMessage(String msg) {
    // create JSON message for Socket.IO (event)
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();

    // add event name
    // Hint: socket.on('event_name', ....
    array.add("toggle_led_value");

    // add payload (parameters) for the event
    JsonObject param = array.createNestedObject();
    param["led_value"] = msg;

    // JSON to String (serializion)
    String output;
    serializeJson(doc, output);
    Serial.println("Sending MSG");
    Serial.println(output);
    Serial.println("Sending MSG");
    // Send event
    socketIO.sendEVENT(output);
}

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
      broadcastMessage(message);
      
  } else {
      // Turn onboard led on
      digitalWrite(2, LOW);
  }
}

void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case sIOtype_DISCONNECT:
            USE_SERIAL.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            USE_SERIAL.printf("[IOc] Connected to url: %s\n", payload);
            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
            doShit(payload, length);
            break;
        case sIOtype_ACK:
            USE_SERIAL.printf("[IOc] get ack: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_ERROR:
            USE_SERIAL.printf("[IOc] get error: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_EVENT:
            USE_SERIAL.printf("[IOc] get binary: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_ACK:
            USE_SERIAL.printf("[IOc] get binary ack: %u\n", length);
            hexdump(payload, length);
            break;
    }
}

void setup() {
    USE_SERIAL.begin(115200);
//    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    // disable AP
    if(WiFi.getMode() & WIFI_AP) {
        WiFi.softAPdisconnect(true);
    }

    WiFiMulti.addAP("NOVA_F518", "room8447");

    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    String ip = WiFi.localIP().toString();
    USE_SERIAL.printf("[SETUP] WiFi Connected %s\n", ip.c_str());

    // server address, port and URL
    socketIO.begin("192.168.5.59", 7700, "/socket.io/?EIO=4");

    // event handler
    socketIO.onEvent(socketIOEvent);
    // On board led
    pinMode(2, OUTPUT);
}

unsigned long messageTimestamp = 0;
void loop() {
    socketIO.loop();
    
    uint64_t now = millis();

    if(now - messageTimestamp > 50) {
        messageTimestamp = now;

        // creat JSON message for Socket.IO (event)
        DynamicJsonDocument doc(1024);
        JsonArray array = doc.to<JsonArray>();

        // add event name
        // Hint: socket.on('event_name', ....
        array.add("event");
        // Read in analog input
        analogInputVal = analogRead(analogPin);

        // add payload (parameters) for the event
        JsonObject param1 = array.createNestedObject();
        param1["mv"] = (uint32_t) analogInputVal;
        param1["now"] = (uint32_t) now;

        // JSON to String (serializion)
        String output;
        serializeJson(doc, output);

        // Send event
        socketIO.sendEVENT(output);

        // Testing ECG signal
        Serial.println(analogInputVal);

        // Print JSON for debugging
        USE_SERIAL.println(output);
        USE_SERIAL.printf("JSON OUTPUT:---",output);
    }
}
