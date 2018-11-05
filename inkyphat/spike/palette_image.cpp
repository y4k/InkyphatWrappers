#include <iostream>
#include <string>

#include <png++/png.hpp>

int main(void)
{
    png::palette inkyPalette(3);
    inkyPalette[0] = png::color(255, 255, 255);
    inkyPalette[1] = png::color(255, 0, 0);
    inkyPalette[2] = png::color(0, 0, 0);

    png::image<png::index_pixel> stripes(212, 104);
    stripes.set_palette(inkyPalette);

    for (png::uint_32 y = 0; y < stripes.get_height(); ++y)
    {
        for (png::uint_32 x = 0; x < stripes.get_width(); ++x)
        {
            stripes[y][x] = x % 3;
            // non-checking equivalent of image.set_pixel(x, y, ...);
        }
    }

    stripes.write("test.png");
    return 0;
}