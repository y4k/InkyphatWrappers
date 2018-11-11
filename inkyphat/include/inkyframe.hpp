#ifndef INKYFRAME_H
#define INKYFRAME_H

#include <stdint.h>
#include <string>
#include <vector>

#include "inkyphatConstants.hpp"

class InkyFrame
{
public:
  InkyFrame();
  InkyFrame(InkyFrame const &);
  void operator=(InkyFrame const &) = delete; // Removed method
  ~InkyFrame();

  int set_pixel(int row, int column, uint8_t value);
  std::string print_current_buffer();

private:
  std::vector<std::vector<uint8_t>> mBuffer;
};

#endif