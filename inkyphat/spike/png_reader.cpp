#include <iostream>
#include <string>

#include <png++/png.hpp>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        std::string fileName = std::string(argv[i]);
        png::image<png::rgb_pixel>
            image(fileName);
        std::cout << "Height:" << image.get_height() << std::endl;
        std::cout << "Width:" << image.get_width() << std::endl;

        for (png::uint_32 y = 0; y < image.get_height(); ++y)
        {
            for (png::uint_32 x = 0; x < image.get_width(); ++x)
            {
                image[y][x] = png::rgb_pixel(x, y, x + y);
                // non-checking equivalent of image.set_pixel(x, y, ...);
            }
        }

        fileName = fileName.substr(0, fileName.size() - 4);
        image.write(fileName + "_test.png");
    }
    return 0;
}