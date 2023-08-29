#include <Arduino.h>

class FastADC {
    public:
        static void init();
        static uint16_t read(uint8_t analogPin);
}