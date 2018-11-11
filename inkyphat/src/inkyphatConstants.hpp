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

// Define some constants
const uint8_t SPI_COMMAND = LOW;
const uint8_t SPI_DATA = HIGH;

const uint8_t V2_RESET = 0x12;

const uint8_t BOOSTER_SOFT_START = 0x06;
const uint8_t POWER_SETTING = 0x01;
const uint8_t POWER_OFF = 0x02;
const uint8_t POWER_ON = 0x04;
const uint8_t PANEL_SETTING = 0x00;
const uint8_t OSCILLATOR_CONTROL = 0x30;
const uint8_t TEMP_SENSOR_ENABLE = 0x41;
const uint8_t RESOLUTION_SETTING = 0x61;
const uint8_t VCOM_DC_SETTING = 0x82;
const uint8_t VCOM_DATA_INTERVAL_SETTING = 0x50;
const uint8_t DATA_START_TRANSMISSION_1 = 0x10;
const uint8_t DATA_START_TRANSMISSION_2 = 0x13;
const uint8_t DATA_STOP = 0x11;
const uint8_t DISPLAY_REFRESH = 0x12;
const uint8_t DEEP_SLEEP = 0x07;

const uint8_t PARTIAL_ENTER = 0x91;
const uint8_t PARTIAL_EXIT = 0x92;
const uint8_t PARTIAL_CONFIG = 0x90;

const uint8_t POWER_SAVE = 0xe3;

const uint8_t WHITE = 0;
const uint8_t BLACK = 1;
const uint8_t RED = 2;
const uint8_t YELLOW = 2;

const int WIDTH = 212;
const int HEIGHT = 104;
// const int WIDTH = 104;
// const int HEIGHT = 212;

#endif