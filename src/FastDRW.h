#include <Arduino.h>

class FastDRW {
    public:
        static void init();
        static bool read(uint8_t digitalPin);
        static void write(uint8_t digitalPin);
}
