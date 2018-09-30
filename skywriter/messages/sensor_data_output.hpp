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
#define SW_OUT_DSP_GESTURE_INFO_NONE 0b00000001                                 // No gesture
#define SW_OUT_DSP_GESTURE_INFO_GARBAGE 0b00000010                              // Garbage model
#define SW_OUT_DSP_GESTURE_INFO_FLICK_WE 0b00000100                             // Flick W -> E
#define SW_OUT_DSP_GESTURE_INFO_FLICK_EW 0b00001000                             // Flick E -> W
#define SW_OUT_DSP_GESTURE_INFO_FLICK_SN 0b00010000                             // Flick S -> N
#define SW_OUT_DSP_GESTURE_INFO_FLICK_NS 0b00100000                             // Flick N -> S
#define SW_OUT_DSP_GESTURE_INFO_CIRCLE_CW 0b01000000                            // Circle clockwise (AirWheel disabled)
#define SW_OUT_DSP_GESTURE_INFO_CIRCLE_CCW 0b10000000                           // Circle counter-clockwise (AirWheel disabled)

#define SW_OUT_DSP_GESTURE_INFO_CLASS 0b1111000000000000                        // 4 bits interpreted as a decimal. 0-Garbage. 1-Flick. 2-Circle

#define SW_OUT_DSP_GESTURE_INFO_CLASS 0b000000010000000000000000                // 1 if flick gesture is classified as an edge flick
#define SW_OUT_DSP_GESTURE_INFO_CLASS 0b10000000000000000000000000000000     // 1 if gesture recognition in progress

// Touch info payload element
#define SW_OUT_DSP_TOUCH_INFO_SIZE 4
#define SW_OUT_DSP_TOUCH_INFO_TOUCH_SOUTH 0b00000001                        // Touch South electrode
#define SW_OUT_DSP_TOUCH_INFO_TOUCH_WEST 0b00000010                         // Touch West electrode
#define SW_OUT_DSP_TOUCH_INFO_TOUCH_NORTH 0b00000100                        // Touch North electrode 
#define SW_OUT_DSP_TOUCH_INFO_TOUCH_EAST 0b00001000                         // Touch East electrode
#define SW_OUT_DSP_TOUCH_INFO_TOUCH_CENTER 0b00010000                       // Touch Center electrode 
#define SW_OUT_DSP_TOUCH_INFO_TAP_SOUTH 0b0000100000                        // Tap South electrode 
#define SW_OUT_DSP_TOUCH_INFO_TAP_WEST 0b0001000000                         // Tap West electrode
#define SW_OUT_DSP_TOUCH_INFO_TAP_NORTH 0b0010000000                        // Tap North electrode 
#define SW_OUT_DSP_TOUCH_INFO_TAP_EAST 0b0100000000                         // Tap East electrode
#define SW_OUT_DSP_TOUCH_INFO_TAP_CENTER 0b1000000000                       // Tap Center electrode 
#define SW_OUT_DSP_TOUCH_INFO_DTAP_SOUTH 0b000010000000000                  // Double tap South electrode 
#define SW_OUT_DSP_TOUCH_INFO_DTAP_WEST 0b000100000000000                   // Double tap West electrode 
#define SW_OUT_DSP_TOUCH_INFO_DTAP_NORTH 0b001000000000000                  // Double tap North electrode 
#define SW_OUT_DSP_TOUCH_INFO_DTAP_EAST 0b010000000000000                   // Double tap East electrode 
#define SW_OUT_DSP_TOUCH_INFO_DTAP_CENTER 0b100000000000000                 // Double tap Center electrode 
#define SW_OUT_DSP_TOUCH_INFO_TOUCH_COUNTER 0b11111111 0000000 00000000     //  8 bit counter determines period between when the hand starts moving to touch until it is detected. Counter * 5ms

// Air Wheel payload element
#define SW_OUT_DSP_WHEEL_INFO_SIZE 2
#define SW_OUT_DSP_WHEEL_INFO_COUNTER 0b11111111 // Counter. AirWheel progression. Incrementing as clockwise. Increment of 32 indicates full rotation.

// XYZ position payload element
// Position info - 0,0,0 is the bottom left corner (South-West at the surface) as 16 bit integers
#define SW_OUT_DSP_POSITION_INFO_SIZE 6
#define SW_OUT_DSP_POSITION_INFO_X 0b1111111111111111                                   // X position
#define SW_OUT_DSP_POSITION_INFO_Y 0b11111111111111110000000000000000                   // Y position
#define SW_OUT_DSP_POSITION_INFO_Z 0b111111111111111100000000000000000000000000000000   // Z position

// Noise power data payload element
// 32 bit float
#define SW_OUT_DSP_NOISE_PWR_SIZE 4

// Uncalibrated data payload element
// 4 or 5 floats depending on number of electrodes.
// S|W|N|E|Center
#define SW_OUT_DSP_CIC_DATA_SIZE_PER_CH 4

// Signal deviation data payload element
// 4 or 5 floats depending on number of electrodes.
// S|W|N|E|Center
#define SW_OUT_DSP_SD_DATA_SIZE_PER_CH 4

#endif