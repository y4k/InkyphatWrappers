#include "pixel.hpp"

Pixel::Pixel()
{
  mColor = DEFAULT_BRIGHTNESS;
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
  mColor = colourInfo;
}

void Pixel::set_pixel_hex(std::string hexValue, uint8_t brightness)
{
  // expects value of form ffffff
  uint32_t result;
  if (hexValue.length() == 6)
  {
    result = stoi(hexValue, NULL, 16);
  }
  result <<= 8;
  set_pixel(result + brightness);
}

uint32_t Pixel::get_pixel_color() const
{
  return mColor;
}

void Pixel::set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br)
{
  // stores entire pixel set in Pixel.colour
  uint32_t result = 0;
  result = (br & 0b111);
  result |= ((uint32_t)r << 24);
  result |= ((uint32_t)g << 16);
  result |= ((uint16_t)b << 8);
  mColor = result;
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

// PixelArray
PixelArray::PixelArray(int numPixels) : mNumPixels{numPixels}
{
  for (int i = 0; i < numPixels; i++)
  {
    mPixelsVector.push_back(Pixel());
  }
}
PixelArray::PixelArray(PixelArray const &pixelArray) : mNumPixels{pixelArray.mNumPixels}
{
  for (int n = 0; n < mNumPixels; n++)
  {
    Pixel p(pixelArray[n]);
    mPixelsVector.push_back(p);
  }
}

void PixelArray::set_pixel(uint32_t colourInfo, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_pixel(colourInfo);
}

void PixelArray::set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_pixel(r, g, b, br);
}

void PixelArray::set_pixel(Pixel const pixel, int x)
{
  mPixelsVector[x] = pixel;
}

Pixel &PixelArray::get_pixel(int p)
{
  return mPixelsVector[p];
}

uint32_t PixelArray::get_pixel_color(int p)
{
  return mPixelsVector[p].get_pixel_color();
}

Pixel const &PixelArray::operator[](const int &index) const
{
  if (index >= 0 && index < mPixelsVector.size())
  {
    return mPixelsVector[index];
  }
  throw std::out_of_range("Index out of range in PixelArray");
}

Pixel &PixelArray::operator[](const int &index)
{
  if (index >= 0 && index < mPixelsVector.size())
  {
    return mPixelsVector[index];
  }
  throw std::out_of_range("Index out of range in PixelArray");
}