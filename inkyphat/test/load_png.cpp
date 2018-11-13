// System includes
#include <cstddef>
#include <iostream>
#include <linux/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <unistd.h> // usleep

#include <png++/png.hpp>

// Local headers
#include "inkyphat.hpp"
#include "inkyframe.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Running InkyPhat CPP Load PNG" << std::endl;

    if (argc != 2)
    {
        std::cout << "Single filename argument required" << std::endl;
        return -1;
    }

    std::string filename(argv[1]);

    // Initialises wiringPi and uses the BCM pin numbering scheme
    if (wiringPiSetupGpio() == -1)
    {
        std::cout << "Failed to initialise WiringPi" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "WiringPi correctly initialised" << std::endl;
    }

    // Setup spi
    // self._spi = spidev.SpiDev()
    // self._spi.open(0, self.mCsPin)
    // self._spi.max_speed_hz = 488000
    if (wiringPiSPISetup(CS0_PIN, 488000) == -1)
    {
        std::cout << "Could not initialise WiringPi SPI library" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "WiringPi SPI library initialised" << std::endl;
    }

    // Load PNG
    png::image<png::rgb_pixel> loaded(filename);

    std::cout << "Width:" << loaded.get_width() << std::endl;
    std::cout << "Height:" << loaded.get_height() << std::endl;

    png::palette inkyPalette(3);
    inkyPalette[0] = png::color(255, 255, 255);
    inkyPalette[1] = png::color(0, 0, 0);
    inkyPalette[2] = png::color(255, 0, 0);

    png::image<png::index_pixel> image(loaded.get_width(), loaded.get_height());
    image.set_palette(inkyPalette);

    for (png::uint_32 y = 0; y < loaded.get_height(); ++y)
    {
        for (png::uint_32 x = 0; x < loaded.get_width(); ++x)
        {
            // std::cout << "[" << x << "," << y << "] (" << unsigned(loaded[y][x].red) << "," << unsigned(loaded[y][x].green) << "," << unsigned(loaded[y][x].blue) << ")" << std::endl;
            if (unsigned(loaded[y][x].blue) <= 50 && unsigned(loaded[y][x].green) <= 50 && unsigned(loaded[y][x].red) <= 50)
            {
                image[y][x] = png::index_pixel(1);
            }
            else if (unsigned(loaded[y][x].blue) >= 220 && unsigned(loaded[y][x].green) >= 220 && unsigned(loaded[y][x].red) >= 220)
            {
                image[y][x] = png::index_pixel(0);
            }
            else if (unsigned(loaded[y][x].blue) <= 50 && unsigned(loaded[y][x].green) <= 50 && unsigned(loaded[y][x].red) >= 220)
            {
                image[y][x] = png::index_pixel(2);
            }
        }
    }

    std::cout << "Width:" << image.get_width() << std::endl;
    std::cout << "Height:" << image.get_height() << std::endl;

    if (image.get_height() > 104 || image.get_width() > 212)
    {
        std::cout << "The dimensions of the image are too large" << std::endl;
        return -2;
    }

    asio::io_context io;

    InkyPhat inky(io);
    InkyFrame frame(inky.get_width(), inky.get_height());

    for (int w = 0; w < image.get_width(); w++)
    {
        for (int h = 0; h < image.get_height(); h++)
        {
            frame.set_pixel(h, w, image[h][w]);
        }
    }

    inky.update(frame);

    io.run();

    return 0;
}
