#include <CustomSPI.h>

CustomSPI::CustomSPI(
    uint8_t data, 
    uint8_t sel, 
    uint8_t clk
): 
    _pin_spi_data(data),
    _pin_spi_sel(sel), 
    _pin_spi_clk(clk) 
{
    // SPI pins for RX control
    pinMode (_pin_spi_sel, OUTPUT);
    pinMode (_pin_spi_data, OUTPUT);
    pinMode (_pin_spi_clk, OUTPUT);

    FastDRW::writeLow(_pin_spi_clk);
    FastDRW::writeHigh(_pin_spi_sel);
    delayMicroseconds(1);
}

void CustomSPI::SERIAL_SENDBIT1() const {
    FastDRW::writeHigh(_pin_spi_data);
    delayMicroseconds(1);
    FastDRW::writeHigh(_pin_spi_clk);
    delayMicroseconds(1);
    FastDRW::writeLow(_pin_spi_clk);
    delayMicroseconds(1);
}

void CustomSPI::SERIAL_SENDBIT0() const {
    FastDRW::writeLow(_pin_spi_data);
    delayMicroseconds(1);
    FastDRW::writeHigh(_pin_spi_clk);
    delayMicroseconds(1);
    FastDRW::writeLow(_pin_spi_clk);
    delayMicroseconds(1);
}