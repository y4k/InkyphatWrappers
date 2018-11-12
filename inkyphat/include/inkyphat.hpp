#ifndef INKYPHAT_H
#define INKYPHAT_H

#include <mutex>
#include <stdint.h>
#include <string>
#include <vector>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <asio.hpp>
#include "inkyframe.hpp"

const int CS0_PIN = 0;

class InkyPhat
{
public:
  InkyPhat(asio::io_context &io);
  InkyPhat(InkyPhat const &) = delete;       // Removed method
  void operator=(InkyPhat const &) = delete; // Removed method
  ~InkyPhat(void);

  asio::io_context &get_io_context() const;

  void update(InkyFrame const &frame);

  int const get_width() const;
  int const get_height() const;

private:
  asio::io_context &mIo;

  uint8_t mCommandPin;
  uint8_t mResetPin;
  uint8_t mBusyPin;
  uint8_t mCsPin;

  int mInkyVersion;
  int mWidth;
  int mHeight;

  uint8_t mBorder = 0b00000000;
  std::vector<uint8_t> mPalette;

  int internal_update(InkyFrame const &frame);
  int display_init();
  int display_update(std::vector<uint8_t> buf_black, std::vector<uint8_t> buf_red);
  int display_finalise();
  int busy_wait();
  int reset();
  int send_command(uint8_t command);
  int send_command(uint8_t command, uint8_t data);
  int send_command(uint8_t command, std::vector<uint8_t> data);
  int send_command(std::vector<uint8_t> command, std::vector<uint8_t> data);
  int send_data(std::vector<uint8_t> data);
  int spi_write(uint8_t level, std::vector<uint8_t> data);
};

#endif