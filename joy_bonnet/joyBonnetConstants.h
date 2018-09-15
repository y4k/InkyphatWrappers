#ifndef JOY_BONNET_CONSTANTS_H
#define JOY_BONNET_CONSTANTS_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <functional>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>

// Button pin definitions - uses the BCM numbering scheme
#define X_BUTTON_PIN 16
#define Y_BUTTON_PIN 13
#define A_BUTTON_PIN 12
#define B_BUTTON_PIN 6
#define START_BUTTON_PIN 26
#define SELECT_BUTTON_PIN 20
#define PLAYER_1_BUTTON_PIN 23
#define PLAYER_2_BUTTON_PIN 22

// I2C communication
#define JOYSTICK_SDA 2
#define JOYSTICK_SCL 5

#define JOYSTICK_OFFSET 800
#define JOYSTICK_ACTIVATION_THRESHOLD 400

// ###################################### ADS1015 microdriver #################################
// # Register and other configuration values:
#define ADS1x15_DEFAULT_ADDRESS        0x48
#define ADS1x15_POINTER_CONVERSION     0x00
#define ADS1x15_POINTER_CONFIG         0x01

#define ADS1015_REG_CONFIG_CQUE_NONE    0x0003 //# Disable the comparator and put ALERT/RDY in high state (default)
#define ADS1015_REG_CONFIG_CLAT_NONLAT  0x0000 //# Non-latching comparator (default)
#define ADS1015_REG_CONFIG_CPOL_ACTVLOW 0x0000 //# ALERT/RDY pin is low when active (default)
#define ADS1015_REG_CONFIG_CMODE_TRAD   0x0000 //# Traditional comparator with hysteresis (default)
#define ADS1015_REG_CONFIG_DR_1600SPS   0x0080 //# 1600 samples per second (default)
#define ADS1015_REG_CONFIG_MODE_SINGLE  0x0100 //# Power-down single-shot mode (default)
#define ADS1015_REG_CONFIG_GAIN_ONE     0x0200 //# gain of 1

#define ADS1015_REG_CONFIG_MUX_SINGLE_0  0x4000 //# channel 0
#define ADS1015_REG_CONFIG_MUX_SINGLE_1  0x5000 //# channel 1
#define ADS1015_REG_CONFIG_MUX_SINGLE_2  0x6000 //# channel 2
#define ADS1015_REG_CONFIG_MUX_SINGLE_3  0x7000 //# channel 3

#define ADS1015_REG_CONFIG_OS_SINGLE     0x8000 //# start a single conversion

#endif