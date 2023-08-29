#ifndef CHANNELS_H
#define CHANNELS_H

#include <Arduino.h>

//default: high 00010000110000010011 low -> PD_IFAF | PD_DIV4 | PD_5GVCO | PD_REG1D8 | PD_DIV80 | PD_PLL1D8
#define PD_VCLAMP       0x00080000 /*Video clamp power down control */
#define PD_VAMP         0x00040000 /*Video amp power down control */
#define PD_IF_DEMOD     0x00020000 /*IF demodulator power down control */
#define PD_IFAF         0x00010000 /*IFAF power down control */
#define PD_RSSI_SQUELCH 0x00008000 /*RSSI & noise squelch power down control */
#define PD_REGBS        0x00004000 /*BS regulator power down control */
#define PD_REGIF        0x00002000 /*IF regulator power down control */
#define PD_BC           0x00001000 /*BC power down control */
#define PD_DIV4         0x00000800 /*Divide-by-4 power down control */
#define PD_5GVCO        0x00000400 /*5G VCO power down control */
#define PD_SYN          0x00000200 /*SYN power down control */
#define PD_AU6M         0x00000100 /*6M audio modulator power down control */
#define PD_6M           0x00000080 /*6M power down control */
#define PD_AU6M5        0x00000040 /*6M5 audio modulator power down control */
#define PD_6M5          0x00000020 /*6M5 power down control */
#define PD_REG1D8       0x00000010 /*1.8V regulator power down control */
#define PD_IFABF        0x00000008 /*IFABF power down control */
#define PD_MIXER        0x00000004 /*RF Mixer power down control */
#define PD_DIV80        0x00000002 /*Divide-by-80 power down control */
#define PD_PLL1D8       0x00000001 /*PLL 1.8V regulator power down control */

#define MAX_BAND 7

#define MIN_TUNE_TIME 30

// Channels to send to the SPI registers
const uint16_t channelTable[] PROGMEM = {
    // Channel 1 - 8
    0x281D, 0x288F, 0x2902, 0x2914, 0x2987, 0x2999, 0x2A0C, 0x2A1E, // Raceband
    0x2A05, 0x299B, 0x2991, 0x2987, 0x291D, 0x2913, 0x2909, 0x289F, // Band A
    0x2903, 0x290C, 0x2916, 0x291F, 0x2989, 0x2992, 0x299C, 0x2A05, // Band B
    0x2895, 0x288B, 0x2881, 0x2817, 0x2A0F, 0x2A19, 0x2A83, 0x2A8D, // Band E
    0x2906, 0x2910, 0x291A, 0x2984, 0x298E, 0x2998, 0x2A02, 0x2A0C, // Band F / Airwave
    0x2609, 0x261C, 0x268E, 0x2701, 0x2713, 0x2786, 0x2798, 0x280B, // Band D / 5.3
    0x248f, 0x2499, 0x2503, 0x250d, 0x2909, 0x2913, 0x291d, 0x2987, //connex
    0x2991, 0x299b, 0x299b, 0x299b, 0x299b, 0x299b, 0x299b, 0x299b  //even more connex, last 6 unused!!!
};

// Channels' MHz Values.
const uint16_t channelFreqTable[] PROGMEM = {
    // Channel 1 - 8
    5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917, // Raceband
    5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725, // Band A
    5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866, // Band B
    5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945, // Band E
    5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880, // Band F / Airwave
    5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621, // Band D / 5.3
    5180, 5200, 5220, 5240, 5745, 5765, 5785, 5805, // connex
    5825, 5845, 5845, 5845, 5845, 5845, 5845, 5845  // even more connex, last 6 unused!!!
};

#endif