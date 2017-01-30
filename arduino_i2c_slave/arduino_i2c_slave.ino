#include <Wire.h>

#define I2C_ADDRESS 8
#define SEND_BUFFER_SIZE 32
#define NUM_SENSORS 1

int16_t sensor_values[NUM_SENSORS];
byte message[SEND_BUFFER_SIZE];

void setup() {
  // Starts listening on I2C_ADDRESS for events
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

/**
 * Called whenever the I2C-master requests data
 */
void requestEvent() {
  // Updates sensor value array
  sensor_values[0] = analogRead(A0);
  // Sends the array over I2C
  send_int16_ts(sensor_values, 1);
}

/**
 * Function for sending array of int16_t over Wire.
 */
void send_int16_ts(int16_t *values, unsigned int num){
  int i;
  for(i = 0; i < num; ++i){
    // Convert every int16_t into two bytes, and append
    // them to the message.
    message[2*i] = (values[i] >> 8) & 0xFF;
    message[2*i + 1] = values[i] & 0xFF;
  }
  // Write the message to Wire,
  Wire.write(message,num*2);
}

