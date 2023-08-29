#include <FastADC.h>

uint16_t FastADC::read(uint8_t analogPin) {
    return analogRead(analogPin);
}