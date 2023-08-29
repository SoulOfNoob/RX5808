#ifndef FASTADC_H
#define FASTADC_H

#include <Arduino.h>

#if defined(ESP32)
    #include <driver/adc.h>
#endif

class FastADC {
    public:
        static void init();
        static uint16_t read(uint8_t analogPin);
};

#endif