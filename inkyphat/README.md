# Inkyphat

## Overview

## Notes

### Pixel addressing

The orientation of the Inkyphat has been taken to be landscape with the longer side of 212 pixels as the top/bottom and the shorter side of 104 pixels as the sides. The top is considered to be the edge where the headers are mounted.

Pixel coordinate are taken from `0` and when addressing an individual pixel, rows or the `y` coordinate are counted from the top downwards whilst columns or the `x` coordinate are counted from the left. This is for the most part to aid when translating a `png` image or similar into an `InkyFrame` as follows

```cpp
InkyPhat inky(io);
InkyFrame frame(inky.get_width(), inky.get_height());

for (int col = 0; col < image.get_width(); col++)
{
    for (int row = 0; row < image.get_height(); row++)
    {
        frame.set_pixel(row, col, image[row][col]);
    }
}
```
