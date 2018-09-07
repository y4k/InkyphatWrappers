// System includes
#include <iostream>
#include <stdint.h>
#include <string>
#include <linux/types.h>
#include <unistd.h>  // usleep
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Local headers
#include "inkyphat.h"
#include "inkyphatConstants.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "No arguments given. Expected 0, 1 or 2." << endl;
        return -1;
    }

    int colour = stoi(argv[1]);

    if(colour < 0 || colour > 2)
    {
        cout << "Expected 0, 1 or 2" << endl;
        return -1;
    }

    cout << "Running InkyPhat CPP" << endl;

    // Initialises wiringPi and uses the wiringPi pin numbering scheme
    if(wiringPiSetupGpio() == -1)
    {
        cout << "Failed to initialise WiringPi" << endl;
        return -1;
    }
    else
    {
        cout << "WiringPi correctly initialised" << endl;
    }

    // Setup spi
    // self._spi = spidev.SpiDev()
    // self._spi.open(0, self.cs_pin)
    // self._spi.max_speed_hz = 488000
    if(wiringPiSPISetup(CS0_PIN, 488000) == -1)
    {
        cout << "Could not initialise WiringPi SPI library" << endl;
        return -1;
    }
    else
    {
        cout << "WiringPi SPI library initialised" << endl;
    }

    InkyPhat inky;

    int width = WIDTH;
    int height = HEIGHT;

    cout << "Setting pixels to given colour:" << colour << endl;
    for (int w = 0; w < width; w++)
    {
        for(int h = 0; h < height; h++)
        {
            if(h%2==0)
            {
                inky.set_pixel(h, w, colour);
            }
            else
            {
                inky.set_pixel(h, w, 0);
            }
        }
    }

    cout << "Display all current pixel values" << endl;
    inky.print_current_buffer();

    inky.update();

    return 0;
}
