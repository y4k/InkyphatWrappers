#ifndef BLINKT_H
#define BLINKT_H

#include <iostream>
#include <mutex>
#include <vector>
#include <unistd.h> // usleep

#include <asio.hpp>
#include <wiringPi.h>

#include "pixel.hpp"

// communication with a Raspberry Pi
const int MOSI = 23;
const int SCLK = 24;

// communication with APA strip
const int APA_SOF = 0b11100000;

class Blinkt
{
public:
  Blinkt(asio::io_context &io);
  Blinkt(Blinkt const &) = delete;
  void operator=(Blinkt const &) = delete;
  ~Blinkt(void);

  asio::io_context &get_io_context();

  void show(PixelArray array);
  void off();
  void fade(PixelArray array, asio::chrono::milliseconds timeout = std::chrono::milliseconds(500));
  // void rise(PixelArray array, int millisecs = 500);
  // void crossfade(PixelArray fromArray, PixelArray toArray, int steps);
  // void crossfade(PixelArray toArray, int steps);

private:
  asio::io_context &mIo;

  uint8_t mMosiPin = MOSI;

  uint8_t mSclkPin = SCLK;

  void update(PixelArray array);
  void write_byte(uint8_t byte);
};

#endif