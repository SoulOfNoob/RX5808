#include <Arduino.h>
#include <RX5808.h>

RX5808 RX1(21, 22, 19, 37);
//RX5808 RX2(23, 18, 5, 38);

uint16_t raw_rssi = 0;

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    RX1.powerUp();
    RX1.setChannel(1, 1);

    Serial.println("Setup Done");
}

void loop() {
    raw_rssi = RX1.getRSSI();
    Serial.printf("RX1 RSSI: %u", raw_rssi);
    delay(250);
}