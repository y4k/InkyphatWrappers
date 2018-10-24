#ifndef INKYPHAT_CONSTANTS_H
#define INKYPHAT_CONSTANTS_H

#include <stdint.h>
#include <wiringPi.h>

//https://pinout.xyz/pinout/inky_phat#

// BCM pin numbering
const int RESET_PIN = 27;
const int BUSY_PIN = 17;
const int COMMAND_PIN = 22;

const int MOSI_PIN = 10;
const int SCLK_PIN = 11;
const int CHIP_SELECT_PIN = 8;
const int CS0_PIN = 0;

// // WiringPi pin numbering
// const int WiPi_BUSY_PIN = 0;
// const int WiPi_RESET_PIN = 2;
// const int WiPi_COMMAND_PIN = 3;

// const int WiPi_MOSI_PIN = 12;
// const int WiPi_SCLK_PIN = 14;
// const int WiPi_CHIP_SELECT_PIN = 10;
// const int WiPi_CS0_PIN = 30;

// Define some constants
const uint8_t _SPI_COMMAND = LOW;
const uint8_t _SPI_DATA = HIGH;

const uint8_t _V2_RESET = 0x12;

const uint8_t _BOOSTER_SOFT_START = 0x06;
const uint8_t _POWER_SETTING = 0x01;
const uint8_t _POWER_OFF = 0x02;
const uint8_t _POWER_ON = 0x04;
const uint8_t _PANEL_SETTING = 0x00;
const uint8_t _OSCILLATOR_CONTROL = 0x30;
const uint8_t _TEMP_SENSOR_ENABLE = 0x41;
const uint8_t _RESOLUTION_SETTING = 0x61;
const uint8_t _VCOM_DC_SETTING = 0x82;
const uint8_t _VCOM_DATA_INTERVAL_SETTING = 0x50;
const uint8_t _DATA_START_TRANSMISSION_1 = 0x10;
const uint8_t _DATA_START_TRANSMISSION_2 = 0x13;
const uint8_t _DATA_STOP = 0x11;
const uint8_t _DISPLAY_REFRESH = 0x12;
const uint8_t _DEEP_SLEEP = 0x07;

const uint8_t _PARTIAL_ENTER = 0x91;
const uint8_t _PARTIAL_EXIT = 0x92;
const uint8_t _PARTIAL_CONFIG = 0x90;

const uint8_t _POWER_SAVE = 0xe3;

const uint8_t WHITE = 0;
const uint8_t BLACK = 1;
const uint8_t RED = 2;
const uint8_t YELLOW = 2;

const int WIDTH = 104;
const int HEIGHT = 212;

#endif