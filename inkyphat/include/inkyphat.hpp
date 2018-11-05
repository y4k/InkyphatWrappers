#ifndef INKYPHAT_H
#define INKYPHAT_H

#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <asio.hpp>

#include "inkyphatConstants.hpp"

class InkyPhat
{
public:
  InkyPhat(asio::io_context &io);
  InkyPhat(InkyPhat const &) = delete;       // Removed method
  void operator=(InkyPhat const &) = delete; // Removed method
  ~InkyPhat(void);

  asio::io_context &get_io_context() const;

  int update();
  int set_pixel(int row, int column, uint8_t value);
  std::string print_current_buffer();

private:
  asio::io_context &mIo;

  std::mutex mLock; // Mutex for thread safety

  uint8_t mCommandPin = COMMAND_PIN;
  uint8_t mResetPin = RESET_PIN;
  uint8_t mBusyPin = BUSY_PIN;
  uint8_t mCsPin = CS0_PIN;

  int mInkyVersion = 2;
  int mWidth = WIDTH;
  int mHeight = HEIGHT;

  std::vector<std::vector<uint8_t>> mBuffer;

  uint8_t mBorder = 0b00000000;
  std::vector<uint8_t> mPalette;

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