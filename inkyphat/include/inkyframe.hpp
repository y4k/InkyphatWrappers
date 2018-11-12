#ifndef INKYFRAME_H
#define INKYFRAME_H

#include <stdint.h>
#include <stdexcept>
#include <string>
#include <vector>

class InkyFrame
{
public:
  InkyFrame(int width, int height);
  InkyFrame(InkyFrame const &);
  void operator=(InkyFrame const &) = delete; // Removed method

  int const get_width() const;
  int const get_height() const;

  uint8_t const get_pixel(int const row, int const column) const;
  int const set_pixel(int const row, int const column, uint8_t const value);

  uint8_t const operator()(int const x, int const y) const;
  int const operator()(int const x, int const y, uint8_t value);

private:
  int mWidth;
  int mHeight;
  std::vector<uint8_t> mBuffer;
};

#endif