#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <string>

#include "blinktConstants.hpp"

class Pixel
{
  public:
    Pixel();
    Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br = DEFAULT_BRIGHTNESS);
    Pixel(uint32_t colourInfo);
    uint32_t colour;
    void setP(uint8_t r, uint8_t g, uint8_t b, uint8_t br);
    void setP(uint32_t colourInfo);
    void setHexPixel(std::string hexValue, uint8_t brightness = 3);
    uint32_t getPixel(); /// returns Pixel.colour

    void setBrightness(uint8_t br);
    uint8_t getBrightness();

    void setColour(uint8_t r, uint8_t g, uint8_t b); // calls setFullPixel with current brightness

  private:
    uint8_t brightness;
};

#endif