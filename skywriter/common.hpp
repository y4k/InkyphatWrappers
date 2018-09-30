#ifndef SW_COMMON_H
#define SW_COMMON_H

#include <stdint.h>

struct Header
{
    uint8_t Size;
    uint8_t Sequence;
    uint8_t ID;
};

struct RuntimeParameterPayload
{
    uint16_t ID;
    uint32_t Arg0;
    uint32_t Arg1;
};

#endif