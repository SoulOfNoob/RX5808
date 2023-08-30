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
}

void CustomSPI::SERIAL_SENDBIT1() const {
    digitalWrite(_pin_spi_data, HIGH);
    delayMicroseconds(1);
    digitalWrite(_pin_spi_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_pin_spi_clk, LOW);
    delayMicroseconds(1);
}

void CustomSPI::SERIAL_SENDBIT0() const {
    digitalWrite(_pin_spi_data, LOW);
    delayMicroseconds(1);
    digitalWrite(_pin_spi_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_pin_spi_clk, LOW);
    delayMicroseconds(1);
}