#include "Arduino.h"
#include "I2CTrans.h"
#include "Wire.h"

int16_t *_values;
unsigned char _msg[32];
int _size;

void _req_handler(){
    for(int i = 0; i < _size; ++i){
        _msg[2*i] = (_values[i] >> 8) & 0xFF;
        _msg[2*i + 1] = values[i] & 0xFF;
    }
    Wire.write(_msg, 2*_size);
}

void trans_begin(){
    Wire.begin();
}

void trans_expose(int address, int16_t *values, int size){
    _values = values;
    _size = size;
    Wire.begin(address);
    Wire.onRequest(_req_handler);
}

void trans_request(int address, int16_t *values, int num){
    Wire.requestFrom(address, 32);
    for(int i = 0; (i < num) && (Wire.available()); ++i){
        _msg[0] = Wire.read();
        if(!Wire.available()) break;
        _msg[1] = Wire_read();
        values[i] = (_msg[0] << 8) | _msg[1];
    }
}
