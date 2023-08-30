#ifndef RX5808_H
#define RX5808_H

#include <Arduino.h>
#include <constants.h>
#include <CustomSPI.h>
#include <SPI.h>

#define MIN_TUNE_TIME 30

enum class State {
    Idle, 
    Busy, 
    PoweredDown,
    Unknown, 
    Tuning
};

class RX5808
{
    private:
        uint8_t _pin_spi_data;
        uint8_t _pin_spi_sel;
        uint8_t _pin_spi_clk;
        uint8_t _pin_rssi;

        uint8_t _current_channel = -1;
        uint8_t _current_band = -1;
        uint16_t _current_frequency = -1;

        CustomSPI _custom_spi;
        State _current_state;
        bool async_mode = false;
        uint8_t _min_tune_time = MIN_TUNE_TIME;

        void PowerDownFeatures(uint32_t features);
        void reset();

    public:
        RX5808(uint8_t pin_ch1, uint8_t pin_ch2, uint8_t pin_ch3, uint8_t pin_rssi);

        void setFrequency(uint16_t frequency);
        void setChannel(uint8_t channel, uint8_t band);

        void cycleChannel();
        uint8_t scanBand(uint8_t band);

        uint16_t getRSSI() const ;


        void powerDown();
        void powerUp();

        void disableTuneTime();
        void enableTuneTime();

        void setState(State state);
        State getState() const ;
        uint8_t getMinTuneTime() const ;
        uint8_t getTuneTime() const ;
};

#endif