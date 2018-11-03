#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>

#include <stdint.h>
#include <stdexcept>
#include <string>
#include <vector>

const uint8_t DEFAULT_BRIGHTNESS = 3;
const int NUM_PIXELS = 8;

class Pixel
{
public:
  Pixel();
  Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br = DEFAULT_BRIGHTNESS);
  Pixel(Pixel const &pixel);

  void set_color(uint8_t r, uint8_t g, uint8_t b);
  void set_full_color(uint8_t r, uint8_t g, uint8_t b, uint8_t br);

  void set_red(uint8_t r);
  void set_green(uint8_t g);
  void set_blue(uint8_t b);
  void set_brightness(uint8_t br);

  uint8_t const get_red() const;
  uint8_t const get_green() const;
  uint8_t const get_blue() const;
  uint8_t const get_brightness() const;

private:
  uint8_t mRed;
  uint8_t mGreen;
  uint8_t mBlue;
  uint8_t mBrightness;
};

class PixelArray
{
public:
  PixelArray(int numPixels = NUM_PIXELS);
  PixelArray(Pixel const &pixel, int numPixels = NUM_PIXELS);
  PixelArray(PixelArray const &pixelArray);

  int const size() const;

  void set_pixel(Pixel pixel, int x = 0);
  void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x = 0);
  void set_pixel(uint8_t r, uint8_t g, uint8_t b, int x = 0);
  void set_pixel_red(uint8_t r, int x = 0);
  void set_pixel_green(uint8_t g, int x = 0);
  void set_pixel_blue(uint8_t b, int x = 0);
  void set_pixel_brightness(uint8_t br, int x = 0);

  Pixel &get_pixel(int p);

  Pixel const &operator[](const int &index) const;
  Pixel &operator[](const int &index);

private:
  int mNumPixels;
  std::vector<Pixel> mPixelsVector;
};

#endif