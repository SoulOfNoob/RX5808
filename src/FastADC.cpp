#include <FastADC.h>

void FastADC::init() {
    #if defined(ESP8266)
        #pragma message "Compile for ESP8266!"
    #elif defined(ESP32)
        adc1_config_width(ADC_WIDTH_12Bit);
        adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);// using GPIO 37
    #else
        #pragma message "Compile for Arduino!"
        //----- ADC IMPROVEMENTS --------------------------------
        // to increase frequency of ADC readings
        // defines for setting and clearing register bits
        #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
        #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

        void initFastADC() {
            // set ADC prescaler to 16 to speedup ADC readings
            sbi(ADCSRA,ADPS2);
            cbi(ADCSRA,ADPS1);
            cbi(ADCSRA,ADPS0);
        }
    #endif
}

uint16_t FastADC::read(uint8_t analogPin) {
    analogRead(analogPin);
    return analogRead(analogPin);
}