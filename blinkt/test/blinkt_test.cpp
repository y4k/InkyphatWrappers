#include <stdint.h>
#include <iostream>
#include <string>
#include <linux/types.h>
#include <unistd.h> // usleep
#include <stdlib.h>
#include "pixel.hpp"
#include "blinkt.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Running Blinkt Test Script" << std::endl;

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

    std::cout << "Creating Blinkt Instance" << std::endl;
    Blinkt &blinkt = Blinkt::Instance();

    Pixel myPixel = Pixel(255, 0, 0, 2);
    uint32_t red = 0xFF000003; // hex codes fit in neatly, of course
    uint32_t green = 0x00FF003;
    uint32_t blue = 0x0000FF03;
    uint32_t white = 0b11111111111111111111111100000011; // Last 0ctet takes APA framing and brightness

    for (int i = 0; i < NUM_LEDS; i++)
    {
        setPixel(blinkt, myPixel, i);
    }
    blinkt.show();

    usleep(3000000);

    setPixel(blinkt, blue);            // default position is Pixel 0
    setPixel(blinkt, blue + green, 1); // Pixels can be set by number
    setPixel(blinkt, green, 2);
    setPixel(blinkt, green + red, 3);
    setPixel(blinkt, red, 4);
    setPixel(blinkt, myPixel.get_pixel(), 5); // pre-defined Pixels can be used to set values
    setPixel(blinkt, white, 6);
    setPixel(blinkt, myPixel, 7); // pre-defined Pixels can be used to set values

    std::cout << "Displaying:" << std::endl
              << "Blue|Blue+Green|Green|Green+Red|Red|White|White"
              << std::endl;

    blinkt.show();
    usleep(2000000);

    Blinkt &AllWhite = Blinkt::Instance();
    for (int i = 0; i < 8; i++)
    {
        setPixel(AllWhite, white, i);
    }

    std::cout << "Displaying:" << std::endl
              << "All White"
              << std::endl;

    AllWhite.show();
    usleep(1000000);

    Blinkt &AllBlack = Blinkt::Instance();

    for (int i = 0; i < 8; i++)
    {
        setPixel(AllBlack, 0, i);
    }

    std::cout << "Displaying:" << std::endl
              << "Nothing"
              << std::endl;

    AllBlack.show();
    usleep(1000000);

    Blinkt &AllRed = Blinkt::Instance();

    for (int i = 0; i < 8; i++)
    {
        setPixel(AllRed, red, i);
    }

    std::cout << "Displaying:" << std::endl
              << "All Red with fade"
              << std::endl;

    AllRed.show();
    usleep(1000000);
    blinkt.fade(2000);

    for (int i = 0; i < 8; i++)
    {
        setPixel(AllBlack, 0, i);
    }

    std::cout << "Displaying:" << std::endl
              << "Nothing"
              << std::endl;

    AllBlack.show();
    usleep(1000000);

    std::cout << "End" << std::endl;
    return 0;
}