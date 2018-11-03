#include "pixel.hpp"

Pixel::Pixel() : Pixel(0, 0, 0, 0)
{
}

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br)
    : mRed{r}, mGreen{g}, mBlue{b}, mBrightness{br}
{
}

Pixel::Pixel(Pixel const &pixel)
    : Pixel(
          pixel.get_red(),
          pixel.get_green(),
          pixel.get_blue(),
          pixel.get_brightness())
{
}

void Pixel::set_color(uint8_t r, uint8_t g, uint8_t b)
{
  set_full_color(r, g, b, get_brightness());
}

void Pixel::set_full_color(uint8_t r, uint8_t g, uint8_t b, uint8_t br)
{
  mRed = r;
  mGreen = g;
  mBlue = b;
  mBrightness = br;
}

void Pixel::set_red(uint8_t r)
{
  mRed = r;
}

void Pixel::set_green(uint8_t g)
{
  mGreen = g;
}

void Pixel::set_blue(uint8_t b)
{
  mBlue = b;
}

void Pixel::set_brightness(uint8_t br)
{
  mBrightness = br;
}

uint8_t const Pixel::get_red() const
{
  return mRed;
}

uint8_t const Pixel::get_green() const
{
  return mGreen;
}

uint8_t const Pixel::get_blue() const
{
  return mBlue;
}

uint8_t const Pixel::get_brightness() const
{
  return mBrightness;
}

// PixelArray
PixelArray::PixelArray(int numPixels) : mNumPixels{numPixels}
{
  for (int i = 0; i < numPixels; i++)
  {
    mPixelsVector.push_back(Pixel());
  }
}

PixelArray::PixelArray(Pixel const &pixel, int numPixels)
    : mNumPixels{numPixels}, mPixelsVector{mNumPixels, pixel}
{
}

PixelArray::PixelArray(PixelArray const &pixelArray) : mNumPixels{pixelArray.mNumPixels}
{
  for (int n = 0; n < mNumPixels; n++)
  {
    Pixel p(pixelArray[n]);
    mPixelsVector.push_back(p);
  }
}

int const PixelArray::size() const
{
  return mNumPixels;
}

void PixelArray::set_pixel(Pixel const pixel, int x)
{
  mPixelsVector[x] = pixel;
}

void PixelArray::set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_full_color(r, g, b, br);
}

void PixelArray::set_pixel(uint8_t r, uint8_t g, uint8_t b, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_color(r, g, b);
}

void PixelArray::set_pixel_red(uint8_t r, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_red(r);
}

void PixelArray::set_pixel_green(uint8_t g, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_green(g);
}

void PixelArray::set_pixel_blue(uint8_t b, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_blue(b);
}

void PixelArray::set_pixel_brightness(uint8_t br, int x)
{
  Pixel &temp = mPixelsVector[x];
  temp.set_brightness(br);
}

Pixel &PixelArray::get_pixel(int p)
{
  return mPixelsVector[p];
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