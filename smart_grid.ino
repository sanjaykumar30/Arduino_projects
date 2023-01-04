
#include <WiFi.h>
#include "HTTPClient.h"
#define VOL 32
const char* ssid = "sanjaykumar";
const char* password = "sanjay1224";



unsigned long last_time = 0;
unsigned long timer_delay = 10000;
float sensor_data=0;
String json_array;
  
void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("First set of readings will appear after 10 seconds");
}

void loop() {
  
  if ((millis() - last_time) > timer_delay) {
  
    if(WiFi.status()== WL_CONNECTED){
    //Write a code to read the sensor and store in sensor_data variable

      sensor_data=analogRead(32);
      Serial.print("voltage:");
      sensor_data=(sensor_data/4095)*5;
      Serial.print(sensor_data);
      Serial.println("V");

      String server ="https://temapi.herokuapp.com/smart_grid/"+String(sensor_data);
      
      json_array = GET_Request(server.c_str());
      Serial.println(json_array);
  
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    last_time = millis();
  }
}

String GET_Request(const char* server) {
  HTTPClient http;    
  http.begin(server);
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return "success";
}
