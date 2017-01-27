#include <Wire.h>

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
}

void loop() {
  delay(100);
}

byte message[2];
int sensor_value;

void requestEvent() {
  sensor_value = analogRead(A0);
  message[0] = (sensor_value >> 8) & 0xFF;
  message[1] = sensor_value & 0xFF;
  Wire.write(message, 2);
}

