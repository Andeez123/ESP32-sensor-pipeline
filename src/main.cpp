#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"
#include "credentials.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 0;



#define DHTPIN 23
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String getLocalTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Failed to obtain time";
  }

  char timeString[64];
  strftime(timeString, sizeof(timeString), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  return String(timeString);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing resources");
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Not connected");
  }
  Serial.println("Connected!");
  dht.begin();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println(getLocalTimeString());
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = dht.readTemperature();
  String time = getLocalTimeString();

  if (WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);

    // specify content type
    http.addHeader("Content-Type", "application/json"); "{\"Temperature\":" + String(temp) + "}";
    String httpPostData = "{\"Sensor\": \"A\", \"Temperature\": " + String(temp) + ", \"Time\": \"" + time + "\"}";
    int httpResponseCode = http.POST(httpPostData);
    Serial.println(httpResponseCode);
    http.end();
  }

  delay(1000); 
}

