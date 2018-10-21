#include "message_parsing.hpp"
#include "skywriterConstants.hpp"

#include <errno.h>
#include <unistd.h>
#include <iostream>

#include <asio.hpp>

#include <wiringPi.h>
#include <wiringPiI2C.h>

void xfr_callback_falling(Skywriter& skywriter);
void xfr_callback_rising(Skywriter& skywriter);

class BaseMessage {
 public:
 protected:
  BaseMessage(uint8_t msgSize, uint8_t sequence, uint8_t id)
      : _msgSize{msgSize}, uint8_t _sequence{sequence}, uint8_t _id{id} {}
  uint8_t _msgSize;
  uint8_t _sequence;
  uint8_t _id
};

class SystemStatusMessage : BaseMessage {
 public:
  SystemStatusMessage(uint8_t msgSize, uint8_t sequence, uint8_t id, int msgId,
                      int maxCmdSize, int errorCode)
      : BaseMessage(msgSize, sequence, id),
        _msgId{msgId},
        _maxCmdSize{msgCmdSize},
        _errorCode{errorCode} {}

 private:
  int _msgId;
  int _maxCmdSize;
  int _errorCode;
};

class Skywriter {
 public:
  Skywriter(asio::io_context& io);
  Skywriter(Skywriter const&) = delete;
  void operator=(Skywriter const&) = delete;
  ~Skywriter();

  asio::io_context& get_io_context();
  void register_callback(SensorOutput output,
                         const std::function<void()> callback);

 private:
  int _i2cFileHandler;
  asio::io_context& _io;

  void start_process();
  void end_process();
  void start_transfer();
  void complete_transfer();
  void read_once();
  void reset();
};