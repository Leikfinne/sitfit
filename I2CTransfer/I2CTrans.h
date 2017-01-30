#ifndef I2CTrans_h
#define I2CTrans_h

void trans_begin();
void trans_expose(int, int16_t *, int);
void trans_request(int, int16_t *, int);

#endif
