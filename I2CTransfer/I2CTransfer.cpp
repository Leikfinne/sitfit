/*
 * I2CTransfer.cpp - Library for transferring an
 * array of int16_ts over I2C. Undefined behaviour
 * if adding more than 16 elements
 *
 * Author: Ludvig S. Jordet
 * Date:   2017-01-30
 */

#include "Arduino.h"
#include "Wire.h"
#include "I2CTransfer.h"

/**
 * Initialize as master
 */
void I2CTransfer::begin(){
    Wire.begin();
}

/**
 * Initialize as slave
 */
void I2CTransfer::begin(int address, void (*onRequest)(void)){
    _req_handler = onRequest;
    Wire.begin(address);
    Wire.onRequest(_intern_handler);
}

void I2CTransfer::_intern_handler(){
    _msg_size = 0;
    _in_handler = 1;
    _req_handler();
    _in_handler = 0;
    Wire.write(_msg, _msg_size);
}

/**
 * Requests a transfer from address, stores the incoming values in
 * the supplied array. Returns the number of values read.
 */
int I2CTransfer::requestData(int address, int16_t *values){
    Wire.requestFrom(address, 32);
    int count = 0;
    for(int i = 0; i < 16 && Wire.available(); ++i){
        _rcv[0] = Wire.read();
        if(!Wire.available) break;
        _rcv[1] = Wire.read();
        values[i] = (_rcv[0] << 8) | _rcv[1];
        ++count;
    }
    return count;
}

/**
 * Adds an int16_t to the message.
 *
 * Only valid when called from the request handler.
 * Returns 1 if an int was added, 0 otherwise
 */
int I2CTransfer::add(int16_t value) {
    if(_in_handler && (_msg_size+2 <= 32)){
        _msg[_msg_size++] = (value >> 8) & 0xFF;
        _msg[_msg_size++] = values & 0xFF;
        return 1;
    } return 0;
}
