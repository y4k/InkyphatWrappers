#ifndef SW_MSG_SENSOR_DATA_OUTPUT_H
#define SW_MSG_SENSOR_DATA_OUTPUT_H

// SENSOR_DATA_OUTPUT Message Definition

/*
The message size is variable.
Data output config mask, timestamp and system info are always present in the message.
The actual configuration can be read from the data output config mask if the payload elements
need to be determined prior to decoding them.

Timestamp - 8 bit counter of 200 Hz (sample interval). Wraps around at 255 ticks.
*/

// Header
#define SW_MSG_SENSOR_DATA_OUTPUT_ID 0x91        // Message ID

// Payload
// Indicates which data is present in the message
#define SW_OUT_CFG_DSP 0b0000000000000001                // DSP Status
#define SW_OUT_CFG_GESTURE 0b0000000000000010            // Gesture Data
#define SW_OUT_CFG_TOUCH 0b0000000000000100              // Touch Data
#define SW_OUT_CFG_WHEEL 0b0000000000001000              // Air Wheel Data
#define SW_OUT_CFG_POS 0b0000000000010000                // Position Data
#define SW_OUT_CFG_NOISE 0b0000000000100000              // Noise Power
#define SW_OUT_CFG_ELECTRODE 0b0000011100000000          // Electrode configuration mask 000= Four cardinal/no center. 001= Five with center.
#define SW_OUT_CFG_UNCAL_SIG_CIC 0b0000100000000000      // Uncalibrated signal data
#define SW_OUT_CFG_SIG_DEV 0b0001000000000000            // Signal deviation data

#define SW_OUT_SYS_INFO_POS_VALID 0b00000001              // Position valid
#define SW_OUT_SYS_INFO_WHEEL_VALID 0b00000010            // Air wheel valid
#define SW_OUT_SYS_INFO_RAW_VALID 0b00000100              // Raw data valid
#define SW_OUT_SYS_INFO_NOISE_VALID 0b00001000            // Noise power valid
#define SW_OUT_SYS_INFO_ENV_NOISE 0b00010000              // Environment noise detected
#define SW_OUT_SYS_INFO_CLIPPING 0b00100000               // ADC is clipping
#define SW_OUT_SYS_INFO_DSP 0b10000000                    // System is currently running. If not set, system about to sleep

// DSP Status payload element
#define SW_OUT_DSP_STATUS_SIZE 2
// First byte contains calibration event info. Second byte indicates current Tx frequency
#define SW_OUT_DSP_STATUS_CAL_FORCED 0b00000010                   // Forced calibration
#define SW_OUT_DSP_STATUS_CAL_START_UP 0b00000100                 // Calibration on start up
#define SW_OUT_DSP_STATUS_CAL_GESTURE 0b00001000                  // Gesture triggered
#define SW_OUT_DSP_STATUS_CAL_NEGATIVE 0b00010000                 // Negative value
#define SW_OUT_DSP_STATUS_CAL_IDLE 0b00100000                     // Idle calibration
#define SW_OUT_DSP_STATUS_CAL_INVALIDITY 0b01000000               // Invalid value calibration
#define SW_OUT_DSP_STATUS_CAL_AFA 0b10000000                      // AFA calibration
#define SW_OUT_DSP_STATUS_TX_FREQ 0b1111111100000000              // Mask to get Tx frequency in kHz (44->115)

// The following are only valid if the corresponding flags have been set. Otherwise the element will not be present in the output.

// Gesture info payload element
#define SW_OUT_DSP_GESTURE_INFO_SIZE 4

// Touch info payload element
#define SW_OUT_DSP_TOUCH_INFO_SIZE 4

// Air Wheel payload element
#define SW_OUT_DSP_WHEEL_INFO_SIZE 2

// XYZ position payload element
#define SW_OUT_DSP_POSITION_INFO_SIZE 6

// Noise power data payload element
#define SW_OUT_DSP_NOISE_PWR_SIZE 4

// Uncalibrated data payload element
#define SW_OUT_DSP_CIC_DATA_SIZE_PER_CH 4

// Signal deviation data payload element
#define SW_OUT_DSP_SD_DATA_SIZE_PER_CH 4


#endif