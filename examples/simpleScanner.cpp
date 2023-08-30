#include <Arduino.h>
#include <RX5808.h>

RX5808 RX1(21, 22, 19, 37);
//RX5808 RX2(23, 18, 5, 38);

uint16_t raw_rssi[8];
uint8_t channels = 8;
bool powerState = 1;
uint16_t loopcount = 0;
unsigned long startmillis = 0;

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    RX1.powerUp();
    RX1.setChannel(0, 0);

    Serial.println("Setup Done");
}

void loop() {
    if(powerState == 1 && loopcount >= 20) {
        RX1.powerDown();
        Serial.println("PowerDown");
        powerState = 0;
        loopcount = 0;
    }else if(powerState == 0 && loopcount >= 20) {
        RX1.powerUp();
        Serial.println("PowerUp");
        powerState = 1;
        loopcount = 0;
    }
    startmillis = millis();
    for (size_t i = 0; i < channels; i++) {
        RX1.setChannel(i, 0);
        raw_rssi[i] = RX1.getRSSI();
    }

    for (size_t i = 0; i < channels; i++)
    {
        Serial.printf("| %d: %d ", (int)i+1, (int)raw_rssi[i]);
    }
    Serial.printf("| scanned %d channels in %d millis \n", channels, millis() - startmillis);
    loopcount++;
}