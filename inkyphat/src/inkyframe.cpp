#include "inkyframe.hpp"

InkyFrame::InkyFrame(int width, int height)
    : mWidth{width},
      mHeight{height},
      mBuffer(mWidth * mHeight)
{
}

InkyFrame::InkyFrame(InkyFrame const &frame) : InkyFrame(frame.mWidth, frame.mHeight)
{
}

int const InkyFrame::get_width() const
{
  return mWidth;
}

int const InkyFrame::get_height() const
{
  return mHeight;
}

uint8_t const InkyFrame::get_pixel(int const row, int const column) const
{
  if (row < 0 || row >= mHeight)
  {
    throw std::out_of_range("row");
  }
  if (column < 0 || column >= mWidth)
  {
    throw std::out_of_range("height");
  }

  int index = row + mHeight * column;
  return mBuffer[index];
}

int const InkyFrame::set_pixel(int const row, int const column, uint8_t const value)
{
  if (row < 0 || row >= mHeight || column < 0 || column >= mWidth || value < 0 || value > 2)
  {
    return -1;
  }
  int index = row + mHeight * column;
  mBuffer[index] = value;
  return 0;
}

uint8_t const InkyFrame::operator()(int const x, int const y) const
{
  return get_pixel(y, x);
}

int const InkyFrame::operator()(int const x, int const y, uint8_t value)
{
  return set_pixel(y, x, value);
}
