#ifndef RX5808_H
#define RX5808_H

#include <Arduino.h>
#include <Channels.h>

#if defined(ESP8266)
    #pragma message "Compile for ESP8266!"
#elif defined(ESP32)
    #pragma message "Compile for ESP32!"
    #include <driver/adc.h>
#else
    #pragma message "Compile for Arduino!"
#endif

#define MIN_TUNE_TIME 30

class RX5808
{
    private:
        uint8_t _pin_ch1;
        uint8_t _pin_ch2;
        uint8_t _pin_ch3;
        uint8_t _pin_rssi;

    public:
        RX5808(uint8_t pin_ch1, uint8_t pin_ch2, uint8_t pin_ch3, uint8_t pin_rssi);

        void setChannel(uint16_t frequency) const;
        void setChannel(uint8_t channel, uint8_t band) const;
        
        uint16_t getRSSI() const;

        void powerDownModule() const;
        void powerUpModule() const;

        void scanChannels();
};

#endif