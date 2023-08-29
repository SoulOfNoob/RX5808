# Generic RX5808 Library

## For Arduino and ESP32/8266

This Library is my attempt to extract the control of the RX5080 module from the projects listed below into a standalone library so it can be used and extended in different projects.

### RX5808 Specifications

- Frequency Range: `5705MHz - 5945MHz`
- Operating Voltage: `3.5V - 5.5V`
- Current Draw: `max 180mA`

To use RX5808 with SPI, some modules need to be modded like this:

> Note: Try using the module unmodded first, the chance is high it "just works"

[SPI Mod Image](https://github.com/sheaivey/rx5808-pro-diversity/blob/develop/docs/rx5808-spi-mod.md)

> Warning: the SPI pins may be damaged by 5V logic like from an Arduino. Use a level shifter or 1kohm-10kohm resistors in front of the SPI pins to avoid damage

### Sources

- [RX5808 Datasheet](https://www.foxtechfpv.com/product/5.8G%20modules/rx5808/RX5808-Spec-V1.pdf)
- [rx5808-pro-diversity](https://github.com/sheaivey/rx5808-pro-diversity/)
- [RotorHazard](https://github.com/RotorHazard/RotorHazard/)
- [Chorus-RF-Laptimer](https://github.com/voroshkov/Chorus-RF-Laptimer/)
- [pidflight-lap-firmware](https://github.com/cmengler/pidflight-lap-firmware/)
