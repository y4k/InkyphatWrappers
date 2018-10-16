#ifndef SW_MSG_REQUEST_MESSAGE_H
#define SW_MSG_REQUEST_MESSAGE_H

#include "common.hpp"

// REQUEST_MESSAGE Message Definition

// Header
#define SW_MSG_REQUEST_MESSAGE_SIZE 0x0C      // Message Size
#define SW_MSG_REQUEST_MESSAGE_ID 0x06        // Message ID

// Payload
#define SW_MSG_REQUEST_MESSAGE_PAYLOAD_ITEMS 3
#define SW_MSG_REQUEST_MESSAGE_PAYLOAD_FORMAT (1,3,4)

Header create_request_message_header();
RequestMessagePayload create_request_message_payload(uint8_t id, uint32_t parameters);
RequestMessagePayload create_request_fw_version();
RequestMessagePayload create_request_trigger();
RequestMessagePayload create_request_signal_match_south();
RequestMessagePayload create_request_signal_match_west();
RequestMessagePayload create_request_signal_match_north();
RequestMessagePayload create_request_signal_match_east();
RequestMessagePayload create_request_signal_match_center();
RequestMessagePayload create_request_electrode_map_south();
RequestMessagePayload create_request_electrode_map_west();
RequestMessagePayload create_request_electrode_map_north();
RequestMessagePayload create_request_electrode_map_east();
RequestMessagePayload create_request_electrode_map_center();
RequestMessagePayload create_request_touch_approach_detection();
RequestMessagePayload create_request_air_wheel();
RequestMessagePayload create_request_gesture_processing();
RequestMessagePayload create_request_calibration_op_mode();
RequestMessagePayload create_request_data_output_enable();
RequestMessagePayload create_request_data_output_lock();
RequestMessagePayload create_request_data_output_request();
RequestMessagePayload create_request_gesture_progress();

#endif