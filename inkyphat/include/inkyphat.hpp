#ifndef INKYPHAT_H
#define INKYPHAT_H

#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <asio.hpp>

const int CS0_PIN = 0;

class InkyPhat
{
public:
  InkyPhat(asio::io_context &io);
  InkyPhat(InkyPhat const &) = delete;       // Removed method
  void operator=(InkyPhat const &) = delete; // Removed method
  ~InkyPhat(void);

  int const operator()(int const x, int const y, uint8_t value);

  asio::io_context &get_io_context() const;

  int update();
  int set_pixel(int row, int column, uint8_t value);
  std::string print_current_buffer();

  int const get_width() const;
  int const get_height() const;

private:
  asio::io_context &mIo;

  std::mutex mLock; // Mutex for thread safety

  uint8_t mCommandPin;
  uint8_t mResetPin;
  uint8_t mBusyPin;
  uint8_t mCsPin;

  int mInkyVersion;
  int mWidth;
  int mHeight;

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