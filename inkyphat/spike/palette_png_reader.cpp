#include <iostream>
#include <string>

#include <png++/png.hpp>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string fileName = std::string(argv[i]);

        png::palette inkyPalette(3);
        inkyPalette[0] = png::color(255, 255, 255);
        inkyPalette[1] = png::color(255, 0, 0);
        inkyPalette[2] = png::color(0, 0, 0);

        png::image<png::index_pixel> image;
        image.set_palette(inkyPalette);

        image.read(fileName);

        std::cout << "Height:" << image.get_height() << std::endl;
        std::cout << "Width:" << image.get_width() << std::endl;

        for (png::uint_32 y = 0; y < image.get_height(); ++y)
        {
            for (png::uint_32 x = 0; x < image.get_width(); ++x)
            {
                if (image[y][x] == 0)
                {
                    image[y][x] = png::index_pixel(1);
                }
                // non-checking equivalent of image.set_pixel(x, y, ...);
            }
        }

        fileName = fileName.substr(0, fileName.size() - 4);
        image.write(fileName + "_test.png");
    }
    return 0;
}