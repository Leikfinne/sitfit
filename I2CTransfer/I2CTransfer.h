/*
 * I2CTransfer.h - Library for transferring an
 * array of int16_ts over I2C. Undefined behaviour
 * if adding more than 16 elements
 *
 * Author: Ludvig S. Jordet
 * Date:   2017-01-30
 */

#ifndef I2CTransfer_h
#define I2CTransfer_h

#include "Arduino.h"

class I2CTransfer {
    public:
        // Master:
        void begin(int slaveAddr);
        // Slave:
        void begin(int address, void (*onRequest)(void));
        int requestData(int address, int16_t *values);
        int add(int16_t value);
    private:
        void _intern_handler();
        int _addr;
        int _in_handler = 0;
        void (*_req_handler)(void);
        unsigned char _msg[32];
        unsigned char _rcv[2];
        int _msg_size;
}
        
#endif // I2CTransfer_h
