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
    if (argc != 3)
    {
        std::cout << "Insufficient arguments given. Expected x,y pair" << std::endl;
        return -1;
    }

    int x = std::stoi(argv[1]);
    int y = std::stoi(argv[2]);

    std::cout << "Running InkyPhat CPP Single Pixel Display Test" << std::endl;

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

    int width = inky.get_width();
    int height = inky.get_height();

    std::cout << "Width:" << width << std::endl;
    std::cout << "Height:" << height << std::endl;

    InkyFrame frame(width, height);

    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            if (frame(w, h, 2) != 0)
            {
                std::cout << "Failed to set pixel (" << w << "," << h << ")" << std::endl;
            }
        }
    }

    if (frame.set_pixel(y, x, 0) != 0)
    {
        std::cout << "Failed to set pixel (" << x << "," << y << ")" << std::endl;
    }

    inky.update(frame);

    io.run();

    return 0;
}
