// S "stem includes
#include <iostream>
#include <stdint.h>
#include <string>
#include <linux/types.h>
#include <unistd.h> // usleep
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Local headers
#include "inkyphat.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "No arguments given. Expected 0, 1 or 2." << std::endl;
        return -1;
    }

    int colour = std::stoi(argv[1]);

    if (colour < 0 || colour > 2)
    {
        std::cout << "Expected 0, 1 or 2" << std::endl;
        return -1;
    }

    std::cout << "Running InkyPhat CPP" << std::endl;

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

    InkyPhat &inky = InkyPhat::Instance();

    int mWidth = WIDTH;
    int mHeight = HEIGHT;

    std::cout << "Setting pixels to given colour:" << colour << std::endl;
    for (int w = 0; w < mWidth; w++)
    {
        for (int h = 0; h < mHeight; h++)
        {
            if (h % 2 == 0)
            {
                inky.set_pixel(h, w, colour);
            }
            else
            {
                inky.set_pixel(h, w, 0);
            }
        }
    }

    std::cout << "Display all current pixel values" << std::endl;
    inky.print_current_buffer();

    inky.update();

    return 0;
}
