#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <Wire.h>

IPAddress ip(10,0,13,101);
IPAddress gateway(10,0,13,1);
IPAddress mask(255,255,255,0);

#define I2C_SLAVE_ADDR 8
#define NUM_SENSORS 1
#define RECV_BUFFER_SIZE 32

char osc_address[] = "/sensors"
IPAddress server_ip(10,0,13,200);
#define SERVER_PORT 1337

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

int16_t sensor_values[NUM_SENSORS];
byte received[2];

void loop() {
  
  Wire.requestFrom(I2C_SLAVE_ADDR, NUM_SENSORS*2);
  for(int i = 0; i < NUM_SENSORS && Wire.available(); ++i){
    received[0] = Wire.read();
    received[1] = Wire.read();
    sensor_values[i] = (received[0] << 8) | received[1];
  }

  OSCMessage msg(osc_address);
  for(int i = 0; i < NUM_SENSORS; ++i){
      msg.add(sensor_values[i]);
  }
  udp.beginPacket(server_ip, SERVER_PORT);
  msg.send(udp);
  udp.endPacket();
  
  delay(10);
}
