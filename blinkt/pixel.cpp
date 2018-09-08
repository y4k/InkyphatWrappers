#include "pixel.h"

Pixel::Pixel()
{
  colour = DEFAULT_BRIGHTNESS;
  colour = DEFAULT_BRIGHTNESS;
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br)  // Always move towards the uint32_t models and try to return those
{
  Pixel();
  setP(r, g, b, br);
}

Pixel::Pixel(uint32_t colourInfo)
{
  Pixel();
  setP(colourInfo);
}

void Pixel::setP(uint32_t colourInfo)
{
  colour = colourInfo;
}

void Pixel::setHexPixel(std::string hexValue, uint8_t brightness)
{  // expects value of form ffffff
  uint32_t result;
  if (hexValue.length() == 6)
  {
    result = stoi(hexValue, NULL, 16);
  }
  result <<=  8;
  setP(result + brightness);
}

uint32_t Pixel::getPixel()
{
  return colour;
}

void Pixel::setP(uint8_t r, uint8_t g, uint8_t b, uint8_t br)
{
  // stores entire pixel set in Pixel.colour
  uint32_t result = 0;
  result = (br & 0b111);
  result |= ((uint32_t)r << 24);
  result |= ((uint32_t)g << 16);
  result |= ((uint16_t)b << 8);
  colour = result;
}

void Pixel::setBrightness(uint8_t br)
{
  uint32_t newValue = (getPixel() & 0xFFFFFF00) + br;
  setP(newValue);
}

uint8_t Pixel::getBrightness()
{
  return (getPixel() & 0b111);
}

void Pixel::setColour(uint8_t r, uint8_t g, uint8_t b)
{
  // calls setP with default brightness or over-ride brightness
  setP(r, g, b, getBrightness());
}