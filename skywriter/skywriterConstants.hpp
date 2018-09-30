#ifndef SW_CONSTANTS_H
#define SW_CONSTANTS_H

// Messages import
#include "messages/fw_version_info.hpp"
#include "messages/request_message.hpp"
#include "messages/sensor_data_output.hpp"
#include "messages/set_runtime_parameter.hpp"
#include "messages/system_status.hpp"

// I2C address
#define SW_ADDR_1 0x42
#define SW_ADDR_2 0x43

// GPIO pins - Broadcom numbering scheme used
#define SW_TRFR_PIN 27
#define SW_RESET_PIN 17
#define SW_SCL_PIN 3
#define SW_SDA_PIN 2

//Additional constants
#define MSG_HEADER_SIZE 4 // Number of bytes

#endif