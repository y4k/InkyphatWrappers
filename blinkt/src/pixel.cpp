#include "pixel.hpp"

Pixel::Pixel()
{
  colour = DEFAULT_BRIGHTNESS;
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br) // Always move towards the uint32_t models and try to return those
{
  Pixel();
  set_pixel(r, g, b, br);
}

Pixel::Pixel(uint32_t colourInfo)
{
  Pixel();
  set_pixel(colourInfo);
}

void Pixel::set_pixel(uint32_t colourInfo)
{
  colour = colourInfo;
}

void Pixel::set_pixel_hex(std::string hexValue, uint8_t brightness)
{ // expects value of form ffffff
  uint32_t result;
  if (hexValue.length() == 6)
  {
    result = stoi(hexValue, NULL, 16);
  }
  result <<= 8;
  set_pixel(result + brightness);
}

uint32_t Pixel::get_pixel_color()
{
  return colour;
}

void Pixel::set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br)
{
  // stores entire pixel set in Pixel.colour
  uint32_t result = 0;
  result = (br & 0b111);
  result |= ((uint32_t)r << 24);
  result |= ((uint32_t)g << 16);
  result |= ((uint16_t)b << 8);
  colour = result;
}

void Pixel::set_brightness(uint8_t br)
{
  uint32_t newValue = (get_pixel_color() & 0xFFFFFF00) + br;
  set_pixel(newValue);
}

uint8_t Pixel::get_brightness()
{
  return (get_pixel_color() & 0b111);
}

void Pixel::set_color(uint8_t r, uint8_t g, uint8_t b)
{
  // calls setP with default brightness or over-ride brightness
  set_pixel(r, g, b, get_brightness());
}

void Blinkt::set_pixel(uint32_t colourInfo, int x)
{
  asio::post(mIo, [&]() {
    Pixel &temp = pVector[x];
    temp.set_pixel(colourInfo);
  });
}

void Blinkt::set_full_pixel(uint32_t colourInfo, int x)
{
  asio::post(mIo, [&]() {
    Pixel &temp = pVector[x];
    temp.set_pixel(colourInfo);
  });
}

void Blinkt::set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x)
{
  asio::post(mIo, [&]() {
    Pixel &temp = pVector[x];
    temp.set_pixel(r, g, b, br);
  });
}

Pixel &Blinkt::get_pixel(int p)
{
  asio::post(mIo, [this, p]() {
    return pVector[p];
  });
}

uint32_t Blinkt::get_pixel_color(int p)
{
  asio::post(mIo, [this, p]() {
    return pVector[p].get_pixel_color();
  });
}

Pixel &PixelArray::operator[](const int &key)
{
  if (key >= 0 && key < mPixelsVector.size())
  {
    return
  }
  throw std::out_of_range("Index out of range in PixelArray");
}