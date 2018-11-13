// System includes
#include <iostream>
#include <stdint.h>
#include <string>
#include <linux/types.h>
#include <unistd.h> // usleep
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "inkyphat.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "No arguments given. Expected 0, 1 or 2." << std::endl;
        return -1;
    }

    int column = std::stoi(argv[1]);

    std::cout << "Running InkyPhat CPP Single Column Display Test" << std::endl;

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

    asio::io_context io;

    InkyPhat inky(io);

    int mWidth = inky.get_width();
    int mHeight = inky.get_height();

    InkyFrame frame(mWidth, mHeight);

    std::cout << "Width:" << mWidth << std::endl;
    std::cout << "Height:" << mHeight << std::endl;

    std::cout << "Setting pixels of a given column:" << column << std::endl;
    for (int w = 0; w < mWidth; w++)
    {
        for (int h = 0; h < mHeight; h++)
        {
            if (w == column)
            {
                if (frame.set_pixel(h, w, 0) != 0)
                {
                    std::cout << "Failed to set pixel (" << 0 << "," << 0 << ")" << std::endl;
                }
            }
            else
            {
                if (frame.set_pixel(h, w, 2) != 0)
                {
                    std::cout << "Failed to set pixel (" << w << "," << h << ")" << std::endl;
                }
            }
        }
    }

    inky.update(frame);
    io.run();

    return 0;
}
