#include "fw_version_info.hpp"

Header create_fw_version_info_header()
{
    struct Header h = {
        .Size = SW_MSG_FW_VERSION_INFO_SIZE,
        .Sequence = 0,
        .ID = SW_MSG_FW_VERSION_INFO_ID
    };
    return h;
}

FwVersionPayload parse_fw_version_info_payload()
{
    struct FwVersionPayload p = {
        
    };
    return p;
}