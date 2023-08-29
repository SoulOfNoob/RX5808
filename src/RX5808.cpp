#include <RX5808.h>

RX5808::RX5808(
    uint8_t pin_ch1, 
    uint8_t pin_ch2, 
    uint8_t pin_ch3, 
    uint8_t pin_rssi
):
    _pin_ch1(pin_ch1), 
    _pin_ch2(pin_ch2), 
    _pin_ch3(pin_ch3), 
    _pin_rssi(pin_rssi) 
{
    
}

void RX5808::setChannel(uint16_t frequency) const {

}
void RX5808::setChannel(uint8_t channel, uint8_t band) const {

}
uint16_t RX5808::getRSSI() const {
    return 0;
}
void RX5808::powerDownModule() const {

}
void RX5808::powerUpModule() const {

}