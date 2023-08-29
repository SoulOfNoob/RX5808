#ifndef FASTADC_H
#define FASTADC_H

#include <Arduino.h>

class FastADC {
    public:
        static uint16_t read(uint8_t analogPin);
};

#endif