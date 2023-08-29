#ifndef CUSTOMSPI_H
#define CUSTOMSPI_H

#include <Arduino.h>
#include <FastDRW.h>

class CustomSPI {
    private:
        uint8_t _pin_spi_data;
        uint8_t _pin_spi_sel;
        uint8_t _pin_spi_clk;
        
    public:
        CustomSPI(uint8_t data, uint8_t sel, uint8_t clk);
        CustomSPI() = default;

        void SERIAL_SENDBIT1() const ;
        void SERIAL_SENDBIT0() const ;
};

#endif