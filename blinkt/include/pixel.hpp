#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <string>

#include "blinkt_constants.hpp"

class Pixel
{
public:
  Pixel();
  Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br = DEFAULT_BRIGHTNESS);
  Pixel(uint32_t colourInfo);
  uint32_t colour;
  void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br);
  void set_pixel(uint32_t colourInfo);
  void set_pixel_hex(std::string hexValue, uint8_t brightness = 3);
  uint32_t get_pixel(); /// returns Pixel.colour

  void set_brightness(uint8_t br);
  uint8_t get_brightness();

  void set_color(uint8_t r, uint8_t g, uint8_t b); // calls set_full_pixel with current brightness

private:
  uint8_t brightness;
};

#endif