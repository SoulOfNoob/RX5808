#ifndef FASTDRW_H
#define FASTDRW_H

#include <Arduino.h>

class FastDRW {
    public:
        static bool read(uint8_t digitalPin);
        static void write(uint8_t digitalPin, bool value);
        static void writeHigh(uint8_t digitalPin);
        static void writeLow(uint8_t digitalPin);
};

#endif