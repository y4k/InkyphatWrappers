// System includes
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
    png::palette inkyPalette(3);
    inkyPalette[0] = png::color(255, 255, 255);
    inkyPalette[1] = png::color(255, 0, 0);
    inkyPalette[2] = png::color(0, 0, 0);

    png::image<png::index_pixel> image;
    image.set_palette(inkyPalette);

    image.read(filename);

    std::cout << "Height:" << image.get_height() << std::endl;
    std::cout << "Width:" << image.get_width() << std::endl;

    if (image.get_height() > 104 || image.get_width() > 212)
    {
        std::cout << "The dimensions of the image are too large" << std::endl;
        return -2;
    }

    asio::io_context io;

    InkyPhat inky(io);

    int mWidth = WIDTH;
    int mHeight = HEIGHT;

    for (int w = 0; w < mWidth; w++)
    {
        for (int h = 0; h < mHeight; h++)
        {
            inky.set_pixel(h, mWidth - w - 1, image[w][h]);
        }
    }

    inky.update();

    return 0;
}