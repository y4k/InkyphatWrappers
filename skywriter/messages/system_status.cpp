#include "common.hpp"
#include "set_runtime_parameter.hpp"

Header create_set_runtime_header()
{
    struct Header h = {
        .Size = SW_MSG_SET_RUNTIME_PARAM_SIZE,
        .Sequence = 0,
        .ID = SW_MSG_SET_RUNTIME_PARAM_ID
        };
    return h;
}

RuntimeParameterPayload create_runtime_payload(uint16_t id, uint32_t arg0, uint32_t arg1)
{
    struct RuntimeParameterPayload p = {
        .ID = id,
        .Arg0 = arg0,
        .Arg1 = arg1
    };
    return p;
}

RuntimeParameterPayload trigger_force_recalibration()
{
    return create_runtime_payload(SW_RUN_PARAM_TRIGGER_ID, SW_RUN_PARAM_TRIGGER_ARG0_RECAL, 0);
}

RuntimeParameterPayload trigger_enter_deep_sleep_1()
{
    return create_runtime_payload(SW_RUN_PARAM_TRIGGER_ID, SW_RUN_PARAM_TRIGGER_ARG0_SLEEP1, 0);
}

RuntimeParameterPayload trigger_enter_deep_sleep_2()
{
    return create_runtime_payload(SW_RUN_PARAM_TRIGGER_ID, SW_RUN_PARAM_TRIGGER_ARG0_SLEEP2, 0);
}

RuntimeParameterPayload persistent_rtps_for_afe()
{
    return create_runtime_payload(SW_RUN_PARAM_MAKE_PERSISTENT_ID, SW_RUN_PARAM_MAKE_PERSISTENT_ARG0_AFE, 0);
}

RuntimeParameterPayload persistent_rtps_for_dsp()
{
    return create_runtime_payload(SW_RUN_PARAM_MAKE_PERSISTENT_ID, SW_RUN_PARAM_MAKE_PERSISTENT_ARG0_DSP, 0);
}

RuntimeParameterPayload persistent_rtps_for_sys()
{
    return create_runtime_payload(SW_RUN_PARAM_MAKE_PERSISTENT_ID, SW_RUN_PARAM_MAKE_PERSISTENT_ARG0_SYS, 0);
}

RuntimeParameterPayload signal_matching_south(uint8_t value)
{
    return create_runtime_payload(SW_RUN_PARAM_AFE_SOUTH_ID, value, 0);
}

RuntimeParameterPayload signal_matching_west(uint8_t value)
{
    return create_runtime_payload(SW_RUN_PARAM_AFE_WEST_ID, value, 0);
}

RuntimeParameterPayload signal_matching_north(uint8_t value)
{
    return create_runtime_payload(SW_RUN_PARAM_AFE_NORTH_ID, value, 0);
}

RuntimeParameterPayload signal_matching_east(uint8_t value)
{
    return create_runtime_payload(SW_RUN_PARAM_AFE_EAST_ID, value, 0);
}

RuntimeParameterPayload signal_matching_center(uint8_t value)
{
    return create_runtime_payload(SW_RUN_PARAM_AFE_CENTER_ID, value, 0);
}

RuntimeParameterPayload electrode_mapping_south(uint8_t channel)
{
    return create_runtime_payload(SW_RUN_PARAM_ELEC_MAP_SOUTH_ID, channel, 0);
}

RuntimeParameterPayload electrode_mapping_west(uint8_t channel)
{
    return create_runtime_payload(SW_RUN_PARAM_ELEC_MAP_WEST_ID, channel, 0);
}

RuntimeParameterPayload electrode_mapping_north(uint8_t channel)
{
    return create_runtime_payload(SW_RUN_PARAM_ELEC_MAP_NORTH_ID, channel, 0);
}

RuntimeParameterPayload electrode_mapping_east(uint8_t channel)
{
    return create_runtime_payload(SW_RUN_PARAM_ELEC_MAP_EAST_ID, channel, 0);
}

RuntimeParameterPayload electrode_mapping_center(uint8_t channel)
{
    return create_runtime_payload(SW_RUN_PARAM_ELEC_MAP_CENTER_ID, channel, 0);
}

RuntimeParameterPayload transmit_freq_select_south(uint8_t numFrequencies)
{
    return create_runtime_payload(SW_RUN_PARAM_ELEC_MAP_CENTER_ID, numFrequencies, 0);
}