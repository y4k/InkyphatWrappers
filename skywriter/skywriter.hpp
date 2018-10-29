#include "../utilities/interruptBase.hpp"
#include "message_parsing.hpp"
#include "skywriterConstants.hpp"

#include <errno.h>
#include <unistd.h>
#include <iostream>

#include <asio.hpp>

#include <wiringPi.h>
#include <wiringPiI2C.h>

class BaseMessage
{
public:
protected:
  BaseMessage(uint8_t msgSize, uint8_t sequence, uint8_t id)
      : _msgSize{msgSize}, _sequence{sequence}, _id{id} {}
  uint8_t _msgSize;
  uint8_t _sequence;
  uint8_t _id;
};

class SystemStatusMessage : BaseMessage
{
public:
  SystemStatusMessage(uint8_t msgSize, uint8_t sequence, uint8_t id, int msgId,
                      int maxCmdSize, int errorCode)
      : BaseMessage(msgSize, sequence, id),
        _msgId{msgId},
        _maxCmdSize{maxCmdSize},
        _errorCode{errorCode} {}

private:
  int _msgId;
  int _maxCmdSize;
  int _errorCode;
};

class Skywriter : InterruptBase
{
public:
  Skywriter(asio::io_context &io);
  Skywriter(Skywriter const &) = delete;
  void operator=(Skywriter const &) = delete;
  ~Skywriter();

  asio::io_context &get_io_context();
  void register_callback(SensorOutputType output,
                         const std::function<void()> callback);

protected:
  void ISR(int pin, int edge) override;

private:
  int _i2cFileHandler;
  asio::io_context &mIo;

  void start_process();
  void start_transfer();
  void complete_transfer();
  void read_once();
  void reset();
};
