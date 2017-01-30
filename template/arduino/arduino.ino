#include <I2CTrans.h>

// TODO: Set number of sensors
#define NUM_SENSORS 0
#define I2C_ADDR 8

char sensors[NUM_SENSORS];

void setup() {
    trans_expose(I2C_ADDR, &sensors, NUM_SENSORS);
}

void loop() {
    // TODO: Update sensor vector
    
    // sensors[0] = ??;
    // ...
}
