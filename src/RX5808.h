#ifndef RX5808_H
#define RX5808_H

#include <Arduino.h>
#include <Channels.h>
#include <FastDRW.h>
#include <FastADC.h>
#include <CustomSPI.h>

// #if defined(ESP8266)
//     #pragma message "Compile for ESP8266!"
// #elif defined(ESP32)
//     #pragma message "Compile for ESP32!"
//     #include <driver/adc.h>
// #else
//     #pragma message "Compile for Arduino!"
// #endif

class RX5808
{
    private:
        uint8_t _pin_spi_data;
        uint8_t _pin_spi_sel;
        uint8_t _pin_spi_clk;
        uint8_t _pin_rssi;
        CustomSPI _custom_spi;

        void PowerDownFeatures(uint32_t features) const ;
        void reset() const ;

    public:
        RX5808(uint8_t pin_ch1, uint8_t pin_ch2, uint8_t pin_ch3, uint8_t pin_rssi);

        uint16_t setFrequency(uint16_t frequency) const ;
        uint16_t setChannel(uint8_t channel, uint8_t band) const ;
        
        uint16_t getRSSI() const ;

        void powerDown() const ;
        void powerUp() const ;

        void scanChannels() const ;
};

#endif