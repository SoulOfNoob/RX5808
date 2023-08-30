#include <RX5808.h>

/**
 * @brief Construct a new RX5808::RX5808 object
 * 
 * @param pin_ch1 CH1 pin of Module (SPI_MISO)
 * @param pin_ch2 CH2 pin of Module (SPI_SS)
 * @param pin_ch3 CH3 pin of Module (SPI_SCLK)
 * @param pin_rssi RSSI pin of Module
 */
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
    setState(State::Idle);
}

uint16_t RX5808::getRSSI() const {
    if(getState() != State::Tuning) {
        analogRead(_pin_rssi);
        return analogRead(_pin_rssi);
    }
    return 0;
}

void RX5808::powerDown() {
    // Power down all features
    PowerDownFeatures(PD_PLL1D8 | PD_DIV80 | PD_MIXER | PD_IFABF | PD_REG1D8 | PD_6M5 | PD_AU6M5 | PD_6M | PD_AU6M | PD_SYN | PD_5GVCO | PD_DIV4 | PD_DIV4 | PD_BC | PD_REGIF | PD_REGBS | PD_RSSI_SQUELCH | PD_IFAF | PD_IF_DEMOD | PD_VAMP | PD_VCLAMP);
    setState(State::PoweredDown);
}

void RX5808::powerUp() {
    reset();
}

//Power Down Control Register
void RX5808::PowerDownFeatures(uint32_t features) {
    uint8_t i;

    setState(State::Busy);

    digitalWrite(_pin_spi_sel, LOW);
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

    digitalWrite(_pin_spi_sel, HIGH);
    delayMicroseconds(1);

    setState(State::Tuning);
    delay(_min_tune_time);
    setState(State::Idle);
}

void RX5808::cycleChannel() {
    if(_current_channel != -1 && _current_band != -1) {
        uint8_t next_channel = _current_channel + 1;
        if (next_channel == 8) next_channel = 0;
        setChannel(next_channel, _current_band);
        // ToDo: only works if setChannel was used to set the frequency...
    }
}

uint8_t RX5808::scanBand(uint8_t band) {
    // ToDo: this will be blocking...
}


// Reset needs to be used to wake the module up if it is completely powered down
void RX5808::reset() {
    setState(State::Busy);

    digitalWrite(_pin_spi_clk, LOW);
    digitalWrite(_pin_spi_sel, LOW);

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
    digitalWrite(_pin_spi_sel, HIGH);
    delayMicroseconds(1);

    setState(State::Tuning);
    delay(_min_tune_time);
    setState(State::Idle);
}

void RX5808::setFrequency(uint16_t frequency) {
    uint8_t i;
    uint16_t channelData;

    channelData = frequency - 479;
    channelData /= 2;
    i = channelData % 32;
    channelData /= 32;
    channelData = (channelData << 7) + i;

    setState(State::Busy);

    // Second is the channel data from the lookup table
    // 20 bytes of register data are sent, but the MSB 4 bits are zeros
    // register address = 0x1, write, data0-15=channelData data15-19=0x0
    digitalWrite(_pin_spi_clk, LOW);
    digitalWrite(_pin_spi_sel, LOW);
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
    digitalWrite(_pin_spi_sel, HIGH);
    delayMicroseconds(1);
    
    setState(State::Tuning);
    delay(_min_tune_time);
    setState(State::Idle);
    _current_frequency = frequency;
}

void RX5808::setChannel(uint8_t channel, uint8_t band) {
    uint16_t frequency = pgm_read_word_near(channelFreqTable + channel + (8 * band));
    setFrequency(frequency);
    _current_channel = channel;
    _current_band = band;
}

/**
 * @brief Disable blocking tune delay, for use in RTOS applications.
 * @note You have to implement non blocking delay yourself
 */
void RX5808::disableTuneTime() {
    _min_tune_time = 0;
}

void RX5808::enableTuneTime() {
    _min_tune_time = MIN_TUNE_TIME;
}

void RX5808::setState(State state) {
    _current_state = state;
}

State RX5808::getState() const {
    return _current_state;
}

uint8_t RX5808::getMinTuneTime() const {
    return MIN_TUNE_TIME;
}

uint8_t RX5808::getTuneTime() const {
    return _min_tune_time;
}