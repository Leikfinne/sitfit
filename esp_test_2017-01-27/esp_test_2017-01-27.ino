#include "ESP8266WiFi.h"

IPAddress ip(10,0,13,101);
IPAddress gateway(10,0,13,1);
IPAddress mask(255,255,255,0);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to Wifi");

  WiFi.config(ip,gateway,mask);
  WiFi.begin("BoxNet", "kylling1");

  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting..");
    delay(200);
  }

  Serial.print("Connected. IP = ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
