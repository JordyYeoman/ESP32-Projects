/*
 * WebSocketClientSocketIO.ino
 *
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include <Hash.h>

ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;

#define USE_SERIAL Serial

bool led_status = false;
uint8_t * payload;
String inData;

//uint8_t * is shorthand for a type of unsigned integer of length 8 bits

void testCode(uint8_t * somethingPayload) {
     Serial.println("PAYLOAD RECIEVED, Running test code: ");
     USE_SERIAL.printf("somethingPayload: ", somethingPayload);
//     Serial.println(payload.led_status)
  }

template <class T>
String type_name(const T&)
{
    String s = __PRETTY_FUNCTION__;
    int start = s.indexOf("[with T = ") + 10;
    int stop = s.lastIndexOf(']');
    return s.substring(start, stop);
}

void doShit(uint8_t * theSamePayloadBra, size_t length) { 
  Serial.println("SHIT HAPPENED");
//  for (int i = 0; i < length; i++) {
//        Serial.println((char)theSamePayloadBra[i]);
//        Serial.println(".........................THE MESSAGE................................");
//  }

  USE_SERIAL.println("-----");
  USE_SERIAL.printf("payloadVal: ", theSamePayloadBra[0]);
  USE_SERIAL.println(" ");
}

void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    USE_SERIAL.println("INCOMING payload----");
    USE_SERIAL.printf("payload: ", payload);
    USE_SERIAL.println("INCOMING payload----");
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
            USE_SERIAL.printf("[IOc] get event: %s\n", payload);
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
    // USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);

    //Serial.setDebugOutput(true);
    USE_SERIAL.setDebugOutput(true);

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
//    socketIO.begin("10.11.100.100", 8880, "/socket.io/?EIO=4");
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

    // Turn onboard led on
    digitalWrite(2, HIGH);

    if(now - messageTimestamp > 2000) {
        messageTimestamp = now;

        // creat JSON message for Socket.IO (event)
        DynamicJsonDocument doc(1024);
        JsonArray array = doc.to<JsonArray>();

        // add event name
        // Hint: socket.on('event_name', ....
        array.add("event_name");

        // add payload (parameters) for the event
        JsonObject param1 = array.createNestedObject();
        param1["now"] = (uint32_t) now;

        // JSON to String (serializion)
        String output;
        serializeJson(doc, output);

        // Send event
        socketIO.sendEVENT(output);

        // Print JSON for debugging
        USE_SERIAL.println(output);
        USE_SERIAL.printf("JSON OUTPUT:---",output);
    }
}
