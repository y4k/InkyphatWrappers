#include "request_message.hpp"
#include "fw_version_info.hpp"
#include "set_runtime_parameter.hpp"

Header create_request_message_header()
{
    struct Header h =
    {
        .Size = SW_MSG_REQUEST_MESSAGE_SIZE,
        .Sequence = 0,
        .ID = SW_MSG_REQUEST_MESSAGE_ID
    };

    return h;
}

RequestMessagePayload create_request_message_payload(uint8_t id, uint32_t parameters)
{
    struct RequestMessagePayload p =
    {
        .MessageID = id,
        .Parameters = parameters
    };
    return p;
}

RequestMessagePayload create_request_fw_version()
{
    return create_request_message_payload(SW_MSG_FW_VERSION_INFO_ID, 0);
}

RequestMessagePayload create_request_trigger()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_TRIGGER_ID);
}

RequestMessagePayload create_request_signal_match_south()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_AFE_SOUTH_ID);
}

RequestMessagePayload create_request_signal_match_west()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_AFE_WEST_ID);
}

RequestMessagePayload create_request_signal_match_north()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_AFE_NORTH_ID);
}

RequestMessagePayload create_request_signal_match_east()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_AFE_EAST_ID);
}

RequestMessagePayload create_request_signal_match_center()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_AFE_CENTER_ID);
}

RequestMessagePayload create_request_electrode_map_south()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_ELEC_MAP_SOUTH_ID);
}

RequestMessagePayload create_request_electrode_map_west()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_ELEC_MAP_WEST_ID);
}

RequestMessagePayload create_request_electrode_map_north()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_ELEC_MAP_NORTH_ID);
}

RequestMessagePayload create_request_electrode_map_east()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_ELEC_MAP_EAST_ID);
}

RequestMessagePayload create_request_electrode_map_center()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_ELEC_MAP_CENTER_ID);
}

RequestMessagePayload create_request_touch_approach_detection()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_TOUCH_ID);
}

RequestMessagePayload create_request_air_wheel()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_AIR_WHEEL_ID);
}

RequestMessagePayload create_request_gesture_processing()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_GESTURE_ID);
}

RequestMessagePayload create_request_calibration_op_mode()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_CAL_OP_ID);
}

RequestMessagePayload create_request_data_output_enable()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_DATA_OUT_ID);
}

RequestMessagePayload create_request_data_output_lock()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_DATA_LOCK_ID);
}

RequestMessagePayload create_request_data_output_request()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_DATA_REQUEST_ID);
}

RequestMessagePayload create_request_gesture_progress()
{
    return create_request_message_payload(SW_MSG_SET_RUNTIME_PARAM_ID, SW_RUN_PARAM_GEST_PROG_ID);
}