#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <OSCMessage.h>
#include <Wire.h>

IPAddress ip(10,0,13,101);
IPAddress gateway(10,0,13,1);
IPAddress mask(255,255,255,0);

IPAddress server_ip(10,0,13,200);
#define server_port 1337

WiFiUDP udp;


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

  Wire.begin();
}

char c;

byte received[2];
int sensor_value;

void loop() {
  Wire.requestFrom(8, 2);
  
  received[0] = Wire.read();
  received[1] = Wire.read();
  sensor_value = (received[0] << 8) | received[1];
  Serial.print("Fikk data, ");
  Serial.println(sensor_value);
  OSCMessage msg("/sensor1");
  msg.add(sensor_value);
  msg.add(sensor_value);
  // put your main code here, to run repeatedly:
  udp.beginPacket(server_ip, server_port);
  msg.send(udp);
  udp.endPacket();
  delay(10);
}
