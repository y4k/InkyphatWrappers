#ifndef SW_MSG_SET_RUNTIME_PARAM_H
#define SW_MSG_SET_RUNTIME_PARAM_H

#include "common.hpp"

// SET_RUNTIME_PARAM Message Definition

// Header
#define SW_MSG_SET_RUNTIME_PARAM_SIZE 0x10      // Message Size
#define SW_MSG_SET_RUNTIME_PARAM_ID 0xA2        // Message ID

// Payload
#define SW_MSG_SET_RUNTIME_PARAM_PAYLOAD_ITEMS 4
#define SW_MSG_SET_RUNTIME_PARAM_PAYLOAD_FORMAT (2,2,4,4)

// Runtime Parameters
#define SW_RUN_PARAM_UNUSED_ARG 0x00000000                      // Unused arg

#define SW_RUN_PARAM_TRIGGER_ID 0x1000                          // Runtime Parameter ID
#define SW_RUN_PARAM_TRIGGER_ARG0_RECAL 0x00000000              // Force recalibration
#define SW_RUN_PARAM_TRIGGER_ARG0_SLEEP1 0x00000002             // Enter Deep Sleep 1
#define SW_RUN_PARAM_TRIGGER_ARG0_SLEEP2 0x00000003             // Enter Deep Sleep 2

// Stores the parameter in the Flash memory
#define SW_RUN_PARAM_MAKE_PERSISTENT_ID 0xFF00                  // Runtime Parameter ID
#define SW_RUN_PARAM_MAKE_PERSISTENT_ARG0_AFE 0x00000000        // Force recalibration
#define SW_RUN_PARAM_MAKE_PERSISTENT_ARG0_DSP 0x00000001        // Enter Deep Sleep 1
#define SW_RUN_PARAM_MAKE_PERSISTENT_ARG0_SYS 0x00000002        // Enter Deep Sleep 2

// Analog Front End - Adjusts the signal level to the given sampling point
#define SW_RUN_PARAM_AFE_SOUTH_ID 0x0050                        // Runtime Parameter ID
#define SW_RUN_PARAM_AFE_WEST_ID 0x0051                         // Runtime Parameter ID
#define SW_RUN_PARAM_AFE_NORTH_ID 0x0052                        // Runtime Parameter ID
#define SW_RUN_PARAM_AFE_EAST_ID 0x0053                         // Runtime Parameter ID
#define SW_RUN_PARAM_AFE_CENTER_ID 0x0054                       // Runtime Parameter ID

// Electrode Mapping - the physical channel number assigned to each electrode
#define SW_RUN_PARAM_ELEC_MAP_SOUTH_ID 0x0065                   // Runtime Parameter ID
#define SW_RUN_PARAM_ELEC_MAP_WEST_ID 0x0066                    // Runtime Parameter ID
#define SW_RUN_PARAM_ELEC_MAP_NORTH_ID 0x0067                   // Runtime Parameter ID
#define SW_RUN_PARAM_ELEC_MAP_EAST_ID 0x0068                    // Runtime Parameter ID
#define SW_RUN_PARAM_ELEC_MAP_CENTER_ID 0x0069                  // Runtime Parameter ID
#define SW_RUN_PARAM_ELEC_MAP_ARG0_CH0 0x00000000               // CHANNEL 0
#define SW_RUN_PARAM_ELEC_MAP_ARG0_CH1 0x00000001               // CHANNEL 1
#define SW_RUN_PARAM_ELEC_MAP_ARG0_CH2 0x00000002               // CHANNEL 2
#define SW_RUN_PARAM_ELEC_MAP_ARG0_CH3 0x00000003               // CHANNEL 3
#define SW_RUN_PARAM_ELEC_MAP_ARG0_CH4 0x00000004               // CHANNEL 4

// Transmit frequency selection
#define SW_RUN_PARAM_TX_FREQ_ID 0x0082                          // Runtime Parameter ID
#define SW_RUN_PARAM_TX_FREQ_ARG0_CH1 0x00000001                // Use 1 channel
#define SW_RUN_PARAM_TX_FREQ_ARG0_CH2 0x00000002                // Use 2 channel
#define SW_RUN_PARAM_TX_FREQ_ARG0_CH3 0x00000003                // Use 3 channel
#define SW_RUN_PARAM_TX_FREQ_ARG0_CH4 0x00000004                // Use 4 channel
#define SW_RUN_PARAM_TX_FREQ_ARG0_CH5 0x00000005                // Use 5 channel

// Touch detection              
#define SW_RUN_PARAM_TOUCH_ID 0x0097                            // Runtime Parameter ID
#define SW_RUN_PARAM_TOUCH_ARG0_ENABLE 0x00000008               // Enable
#define SW_RUN_PARAM_TOUCH_ARG0_DISABLE 0x00000000              // Disable
#define SW_RUN_PARAM_TOUCH_ARG1_REQUIRED 0x00000008             // REQUIRED!

// Approach detection              
#define SW_RUN_PARAM_APPROACH_ID 0x0097                            // Runtime Parameter ID
#define SW_RUN_PARAM_APPROACH_ARG0_ENABLE 0x00000001               // Enable
#define SW_RUN_PARAM_APPROACH_ARG0_DISABLE 0x00000000              // Disable
#define SW_RUN_PARAM_APPROACH_ARG1_REQUIRED 0x00000001             // REQUIRED!

// Air wheel detection              
#define SW_RUN_PARAM_AIR_WHEEL_ID 0x0090                            // Runtime Parameter ID
#define SW_RUN_PARAM_AIR_WHEEL_ARG0_ENABLE 0x00000020               // Enable
#define SW_RUN_PARAM_AIR_WHEEL_ARG0_DISABLE 0x00000000              // Disable
#define SW_RUN_PARAM_AIR_WHEEL_ARG1_REQUIRED 0x00000020             // REQUIRED!

// Gesture detection              
/*
Set a bit as 1 to enable a feature. Set 0 to disable.
Arg1 acts as a bitmask so to change the flag in ARG0, the corresponding bit in ARG1
must be set
*/
#define SW_RUN_PARAM_GESTURE_ID 0x0085                              // Runtime Parameter ID
#define SW_RUN_PARAM_GESTURE_ARG_PADDING 0x000000                   // 3 byte padding - ARG0/1 need 4 bytes
#define SW_RUN_PARAM_GESTURE_ARG_GARBAGE 0b00000001                 //  Garbage mask
#define SW_RUN_PARAM_GESTURE_ARG_FLICK_WE 0b00000010                //  Flick W -> E mask
#define SW_RUN_PARAM_GESTURE_ARG_FLICK_EW 0b00000100                //  Flick E -> W mask
#define SW_RUN_PARAM_GESTURE_ARG_FLICK_SN 0b00001000                //  Flick S -> N mask
#define SW_RUN_PARAM_GESTURE_ARG_FLICK_NS 0b00010000                //  Flick N -> S mask
#define SW_RUN_PARAM_GESTURE_ARG_CIRCLE_CW 0b00100000               //  CW Circle
#define SW_RUN_PARAM_GESTURE_ARG_CIRCLE_CCW 0b01000000              //  CCW Circle

// Calibration operation mode
/*
Set a bit as 1 to enable a feature. Set 0 to disable.
Arg1 acts as a bitmask so to change the flag in ARG0, the corresponding bit in ARG1
must be set
*/
#define SW_RUN_PARAM_CAL_OP_ID 0x0080                               // Runtime Parameter ID
#define SW_RUN_PARAM_CAL_OP_ARG_PADDING 0x000000                    // 3 byte padding - ARG0/1 need 4 bytes
#define SW_RUN_PARAM_CAL_OP_ARG_START_UP 0b00000001                 // Start up calibration
#define SW_RUN_PARAM_CAL_OP_ARG_GESTURE 0b00000010                  // Gesture triggered calibration
#define SW_RUN_PARAM_CAL_OP_ARG_NEGATIVE 0b00000100                 // Negative triggered calibration
#define SW_RUN_PARAM_CAL_OP_ARG_IDLE 0b00001000                     // Idle triggered calibration
#define SW_RUN_PARAM_CAL_OP_ARG_INVALIDITY 0b00010000               // Invalidity value (out of range) triggered calibration
#define SW_RUN_PARAM_CAL_OP_ARG_AFA 0b00100000                      // AFA triggered calibration

// Data output mode
/*
If a feature is disabled here, the output of that feature is not present in the sensor data output payload.

Set a bit as 1 to enable a feature. Set 0 to disable.
Arg1 acts as a bitmask so to change the flag in ARG0, the corresponding bit in ARG1
must be set
*/
#define SW_RUN_PARAM_DATA_OUT_ID 0x00A0                                 // Runtime Parameter ID
#define SW_RUN_PARAM_DATA_OUT_ARG_PADDING 0x000000                      // 3 byte padding - ARG0/1 need 4 bytes
#define SW_RUN_PARAM_DATA_OUT_ARG_DSP 0b0000000000000001                // DSP Status
#define SW_RUN_PARAM_DATA_OUT_ARG_GESTURE 0b0000000000000010            // Gesture Data
#define SW_RUN_PARAM_DATA_OUT_ARG_TOUCH 0b0000000000000100              // Touch Data
#define SW_RUN_PARAM_DATA_OUT_ARG_WHEEL 0b0000000000001000              // Air Wheel Data
#define SW_RUN_PARAM_DATA_OUT_ARG_POS 0b0000000000010000                // Position Data
#define SW_RUN_PARAM_DATA_OUT_ARG_NOISE 0b0000000000100000              // Noise Power
#define SW_RUN_PARAM_DATA_OUT_ARG_RES6 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_RES7 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_RES8 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_RES9 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_RES10 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_UNCAL_SIG_CIC 0b0000100000000000      // Uncalibrated signal data
#define SW_RUN_PARAM_DATA_OUT_ARG_SIG_DEV 0b0001000000000000            // Signal deviation data
#define SW_RUN_PARAM_DATA_OUT_ARG_RES13 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_RES14 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_OUT_ARG_RES15 0b0000000000000000              // RESERVED = 0

// Data output lock mask
/*
If a feature is enabled here, the output of that feature is always present in the sensor data
output message regardless of whether there is new data or not. If disabled, then the payload element
is present only when the data is updated. (Payload element is variable)

Set a bit as 1 to enable a feature. Set 0 to disable.
Arg1 acts as a bitmask so to change the flag in ARG0, the corresponding bit in ARG1
must be set
*/
#define SW_RUN_PARAM_DATA_LOCK_ID 0x00A1                                 // Runtime Parameter ID
#define SW_RUN_PARAM_DATA_LOCK_ARG_PADDING 0x000000                      // 3 byte padding - ARG0/1 need 4 bytes
#define SW_RUN_PARAM_DATA_LOCK_ID 0x00A0                                 // Runtime Parameter ID
#define SW_RUN_PARAM_DATA_LOCK_ARG_PADDING 0x000000                      // 3 byte padding - ARG0/1 need 4 bytes
#define SW_RUN_PARAM_DATA_LOCK_ARG_DSP 0b0000000000000001                // DSP Status
#define SW_RUN_PARAM_DATA_LOCK_ARG_GESTURE 0b0000000000000010            // Gesture Data
#define SW_RUN_PARAM_DATA_LOCK_ARG_TOUCH 0b0000000000000100              // Touch Data
#define SW_RUN_PARAM_DATA_LOCK_ARG_WHEEL 0b0000000000001000              // Air Wheel Data
#define SW_RUN_PARAM_DATA_LOCK_ARG_POS 0b0000000000010000                // Position Data
#define SW_RUN_PARAM_DATA_LOCK_ARG_NOISE 0b0000000000100000              // Noise Power
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES6 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES7 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES8 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES9 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES10 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_UNCAL_SIG_CIC 0b0000100000000000      // Uncalibrated signal data
#define SW_RUN_PARAM_DATA_LOCK_ARG_SIG_DEV 0b0001000000000000            // Signal deviation data
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES13 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES14 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_LOCK_ARG_RES15 0b0000000000000000              // RESERVED = 0

// Data output request mask
/*
If a feature is enabled here, the output of that feature is present in the next sensor data
output message regardless of whether there is new data or not. If disabled, then the payload element
will not contain that element. This is in accordance with the output enable and output lock masks

Set a bit as 1 to enable a feature. Set 0 to disable.
Arg1 acts as a bitmask so to change the flag in ARG0, the corresponding bit in ARG1
must be set
*/
#define SW_RUN_PARAM_DATA_REQUEST_ID 0x00A2                                 // Runtime Parameter ID
#define SW_RUN_PARAM_DATA_REQUEST_ARG_PADDING 0x000000                      // 3 byte padding - ARG0/1 need 4 bytes
#define SW_RUN_PARAM_DATA_REQUEST_ARG_DSP 0b0000000000000001                // DSP Status
#define SW_RUN_PARAM_DATA_REQUEST_ARG_GESTURE 0b0000000000000010            // Gesture Data
#define SW_RUN_PARAM_DATA_REQUEST_ARG_TOUCH 0b0000000000000100              // Touch Data
#define SW_RUN_PARAM_DATA_REQUEST_ARG_WHEEL 0b0000000000001000              // Air Wheel Data
#define SW_RUN_PARAM_DATA_REQUEST_ARG_POS 0b0000000000010000                // Position Data
#define SW_RUN_PARAM_DATA_REQUEST_ARG_NOISE 0b0000000000100000              // Noise Power
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES6 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES7 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES8 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES9 0b0000000000000000               // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES10 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_UNCAL_SIG_CIC 0b0000100000000000      // Uncalibrated signal data
#define SW_RUN_PARAM_DATA_REQUEST_ARG_SIG_DEV 0b0001000000000000            // Signal deviation data
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES13 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES14 0b0000000000000000              // RESERVED = 0
#define SW_RUN_PARAM_DATA_REQUEST_ARG_RES15 0b0000000000000000              // RESERVED = 0

// Gesture in progress flag control
/*
Determines whether the gesture in progress output is part of the sensor data output
*/

#define SW_RUN_PARAM_GEST_PROG_ID 0x00A3                                    // Runtime Parameter ID
#define SW_RUN_PARAM_GEST_PROG_ARG0_ENABLE 0x00000000                       // Enabled
#define SW_RUN_PARAM_GEST_PROG_ARG0_DISABLE 0x00000001                      // Disabled
#define SW_RUN_PARAM_GEST_PROG_ARG1 0x00000001                              // Required

Header create_set_runtime_header();
RuntimeParameterPayload create_set_runtime_trigger_payload();

#endif