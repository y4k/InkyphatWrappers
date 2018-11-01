#ifndef PIXEL_H
#define PIXEL_H

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
  Pixel(uint32_t colourInfo);

  void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br);
  void set_pixel(uint32_t colourInfo);
  void set_pixel_hex(std::string hexValue, uint8_t brightness = 3);
  // uint32_t get_pixel_color();
  uint32_t get_pixel_color() const;

  void set_brightness(uint8_t br);
  uint8_t get_brightness();

  void set_color(uint8_t r, uint8_t g, uint8_t b); // calls set_full_pixel with current brightness

private:
  uint32_t mColor;
  uint8_t brightness;
};

class PixelArray
{
public:
  PixelArray(int numPixels = NUM_PIXELS);
  PixelArray(PixelArray const &pixelArray);

  void set_pixel(Pixel pixel, int x = 0);
  void set_pixel(uint32_t pixel, int x = 0);
  void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x = 0);

  Pixel &get_pixel(int p);
  uint32_t get_pixel_color(int p);

  Pixel const &operator[](const int &index) const;
  Pixel &operator[](const int &index);

private:
  int mNumPixels;
  std::vector<Pixel> mPixelsVector;
};

inline void set_pixel(PixelArray &pixelArray, uint32_t p = 7, int x = 0)
{
  pixelArray.set_pixel(p, x);
}

inline void set_pixel(PixelArray &pixelArray, Pixel &p, int x = 0)
{
  uint32_t pixelValue = p.get_pixel_color();
  set_pixel(pixelArray, pixelValue, x);
}

#endif