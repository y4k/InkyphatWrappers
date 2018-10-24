#ifndef BLINKT_CONSTANTS_H
#define BLINKT_CONSTANTS_H

#include <stdint.h>   // fixed width ints to hold Pixel values

//https://pinout.xyz/pinout/blinkt#

// communication with a Raspberry Pi
const int MOSI=23;
const int SCLK=24;

/*
  APA102 strip wakes on high, and sends brightness frame first.  Always &ed with this:
 */

// communication with APA strip
const int APA_SOF = 0b11100000;

// Constants for defaults in functions
const int NUM_LEDS = 8;
const uint8_t DEFAULT_BRIGHTNESS = 3;

#endif