#include <FastDRW.h>

bool FastDRW::read(uint8_t digitalPin) {
    // Optimize later based on MCU
    return digitalRead(digitalPin);
};
void FastDRW::write(uint8_t digitalPin, bool value) {
    // Optimize later based on MCU
    digitalWrite(digitalPin, value);
};

void FastDRW::writeHigh(uint8_t digitalPin) {
    // Optimize later based on MCU
    digitalWrite(digitalPin, HIGH);
};

void FastDRW::writeLow(uint8_t digitalPin) {
    // Optimize later based on MCU
    digitalWrite(digitalPin, LOW);
};