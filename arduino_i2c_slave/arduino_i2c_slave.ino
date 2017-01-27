#include <Wire.h>

#define I2C_ADDRESS 8
#define SEND_BUFFER_SIZE 128
#define NUM_SENSORS 1

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

int16_t sensor_values[NUM_SENSORS];

void requestEvent() {
  sensor_values[0] = analogRead(A0);
  send_int16_ts(sensor_values, 1);
}

byte message[SEND_BUFFER_SIZE];
void send_int16_ts(int16_t *values, unsigned int num){
  int i;
  for(i = 0; i < num; ++i){
    message[2*i] = (values[i] >> 8) & 0xFF;
    message[2*i + 1] = values[i] & 0xFF;
  }
  Wire.write(message,num*2);
}

