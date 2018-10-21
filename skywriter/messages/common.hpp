#ifndef SW_COMMON_H
#define SW_COMMON_H

#include <stdint.h>

class Header
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

struct RequestMessagePayload
{
    uint8_t MessageID;
    uint32_t Parameters;
};

struct FwVersionPayload
{
    uint8_t FwValid;
    uint16_t HwRev;
    uint8_t ParameterStartAddr;
    uint8_t LibraryLoaderVersion[3];
    uint8_t FwStartAddr;
    uint8_t FwVersion[120];
};

#endif