#include "skywriterConstants.hpp"
#include <iostream>

enum SensorOutputType
{
    FLICK,
    TOUCH,
    TAP,
    DOUBLE,
    AIRWHEEL,
    POSITION
};

class BaseReceivedMessage
{
  public:
  protected:
    BaseReceivedMessage(uint8_t size, uint8_t sequence, uint8_t id);
    uint8_t Size;
    uint8_t Sequence;
    uint8_t ID;
};

class SensorOutput : BaseReceivedMessage
{
  public:
    SensorOutput(uint8_t size, uint8_t sequence, uint8_t id);

  protected:
  private:
};

Header parse_header(char bytes[]);
void parse_sensor_data_output(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t *payload);
void parse_system_status(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t *payload);
void parse_fw_info(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t *payload);
void print_header(uint8_t msgSize, uint8_t sequence, uint8_t id);
int combine_bytes(int numBytes, uint8_t *bytes);