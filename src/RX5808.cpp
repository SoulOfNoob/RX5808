#include <RX5808.h>

RX5808::RX5808(
    uint8_t pin_ch1, 
    uint8_t pin_ch2, 
    uint8_t pin_ch3, 
    uint8_t pin_rssi
):
    _pin_spi_data(pin_ch1), 
    _pin_spi_sel(pin_ch2), 
    _pin_spi_clk(pin_ch3), 
    _pin_rssi(pin_rssi),
    _custom_spi(pin_ch1, pin_ch2, pin_ch3)
{
    FastADC::init();
    PowerDownFeatures(PD_IFAF | PD_DIV4 | PD_5GVCO | PD_REG1D8 | PD_DIV80 | PD_PLL1D8 | PD_IF_DEMOD | PD_VAMP | PD_VCLAMP | PD_MIXER | PD_IFABF | PD_6M5 | PD_AU6M5 | PD_6M | PD_AU6M | PD_SYN | PD_REGIF);
}

uint16_t RX5808::getRSSI() const {
    return FastADC::read(_pin_rssi);
}

void RX5808::powerDown() const {
    // Power down all features
    PowerDownFeatures(PD_PLL1D8 | PD_DIV80 | PD_MIXER | PD_IFABF | PD_REG1D8 | PD_6M5 | PD_AU6M5 | PD_6M | PD_AU6M | PD_SYN | PD_5GVCO | PD_DIV4 | PD_DIV4 | PD_BC | PD_REGIF | PD_REGBS | PD_RSSI_SQUELCH | PD_IFAF | PD_IF_DEMOD | PD_VAMP | PD_VCLAMP);
}

void RX5808::powerUp() const {
    reset();
}

//Power Down Control Register
void RX5808::PowerDownFeatures(uint32_t features) const {
    uint8_t i;
    FastDRW::writeLow(_pin_spi_sel);
    delayMicroseconds(1);
    
    // send 0x0A
    _custom_spi.SERIAL_SENDBIT0();
    _custom_spi.SERIAL_SENDBIT1();
    _custom_spi.SERIAL_SENDBIT0();
    _custom_spi.SERIAL_SENDBIT1();

    _custom_spi.SERIAL_SENDBIT1();

    for (i = 20; i > 0; i--) {
        // Is bit high or low?
        if (features & 0x1) {
            _custom_spi.SERIAL_SENDBIT1();
        }
        else {
            _custom_spi.SERIAL_SENDBIT0();
        }
        features >>= 1;
    }

    FastDRW::writeHigh(_pin_spi_sel);
    delayMicroseconds(1);
    delay(MIN_TUNE_TIME);
}


// Reset needs to be used to wake the module up if it is completely powered down
void RX5808::reset() const {
    FastDRW::writeLow(_pin_spi_clk);
    FastDRW::writeLow(_pin_spi_sel);
    delayMicroseconds(1);

    // State register 0x0F
    _custom_spi.SERIAL_SENDBIT1();
    _custom_spi.SERIAL_SENDBIT1();
    _custom_spi.SERIAL_SENDBIT1();
    _custom_spi.SERIAL_SENDBIT1();

    // write
    _custom_spi.SERIAL_SENDBIT1();

    // set all bits to zero -> reset
    for (int i = 20; i > 0; i--) {
        _custom_spi.SERIAL_SENDBIT0();
    }

    // Finished clocking data in
    FastDRW::writeHigh(_pin_spi_sel);
    delayMicroseconds(1);

    delay(MIN_TUNE_TIME);
}

uint16_t RX5808::setFrequency(uint16_t frequency) const {
    uint8_t i;
    uint16_t channelData;

    channelData = frequency - 479;
    channelData /= 2;
    i = channelData % 32;
    channelData /= 32;
    channelData = (channelData << 7) + i;

    // Second is the channel data from the lookup table
    // 20 bytes of register data are sent, but the MSB 4 bits are zeros
    // register address = 0x1, write, data0-15=channelData data15-19=0x0
    FastDRW::writeLow(_pin_spi_clk);
    FastDRW::writeLow(_pin_spi_sel);
    delayMicroseconds(1);

    // Register 0x1
    _custom_spi.SERIAL_SENDBIT1();
    _custom_spi.SERIAL_SENDBIT0();
    _custom_spi.SERIAL_SENDBIT0();
    _custom_spi.SERIAL_SENDBIT0();

    // Write to register
    _custom_spi.SERIAL_SENDBIT1();

    // D0-D15
    //   note: loop runs backwards as more efficent on AVR
    for (i = 16; i > 0; i--) {
        // Is bit high or low?
        if (channelData & 0x1) {
            _custom_spi.SERIAL_SENDBIT1();
        }
        else {
            _custom_spi.SERIAL_SENDBIT0();
        }
        // Shift bits along to check the next one
        channelData >>= 1;
    }

    // Remaining D16-D19
    for (i = 4; i > 0; i--) {
        _custom_spi.SERIAL_SENDBIT0();
    }

    // Finished clocking data in
    FastDRW::writeHigh(_pin_spi_sel);
    delayMicroseconds(1);
    
    delay(MIN_TUNE_TIME);
    
    return frequency;
}

uint16_t RX5808::setChannel(uint8_t channel, uint8_t band) const {
    uint16_t frequency = pgm_read_word_near(channelFreqTable + channel + (8 * band));
    return setFrequency(frequency);
}