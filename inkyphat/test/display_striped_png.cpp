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

int main(void)
{
    std::cout << "Running InkyPhat CPP Display Striped PNG" << std::endl;

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

    // Create PNG
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

    asio::io_context io;

    InkyPhat inky(io);

    int mWidth = WIDTH;
    int mHeight = HEIGHT;

    for (int w = 0; w < mWidth; w++)
    {
        for (int h = 0; h < mHeight; h++)
        {
            inky.set_pixel(h, w, stripes[w][h]);
        }
    }

    inky.update();

    return 0;
}