/*
   ESP8266 HTTP Lock by Yan
   Make a Siri HomeKit enabled lock with ESPea (https://blog.aprbrother.com/product/espea)
   This example code is in the public domain
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define RELAY_PIN 5     // wire D1 to relay 

const char* ssid        = "YOUR-SSID";
const char* password    = "YOUR-PASSWORD";
const long  lockTimeout = 3000;

ESP8266WebServer server(80);
long unlockedTime = 0;

void handleQuery() {
    char rsp[255];
    sprintf(rsp, "{\"state\":\"%s\",\"statusCode\":200}", digitalRead(RELAY_PIN) ? "locked" : "unlocked");
    server.send(200, "text/plain", rsp);
}

void handleLock() {
    digitalWrite(RELAY_PIN, 1);
    // Lock again after 3 seconds
    unlockedTime = millis();
    server.send(200, "text/plain", "{\"battery\":100,\"statusCode\":200}");
}

void setup() {
    Serial.begin(115200);
    pinMode(RELAY_PIN, OUTPUT);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, handleQuery);          // Query lock status
    server.on("/", HTTP_POST, handleLock);          // Set lock status
    server.begin();

}

void loop() {
    server.handleClient();

    // Restore lock status
    if ((unlockedTime > 0) && (millis() - unlockedTime > lockTimeout)) {
        unlockedTime = 0;
        digitalWrite(RELAY_PIN, 0);
    }
}
