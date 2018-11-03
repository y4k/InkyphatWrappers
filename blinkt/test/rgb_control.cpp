#include <iostream>
#include <functional>

#include <asio.hpp>

#include "pixel.hpp"
#include "blinkt.hpp"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cout << "Number of additional args must be 4. Received:" << (argc - 1) << std::endl;
        return -1;
    }

    uint8_t red = atoi(argv[1]);
    uint8_t green = atoi(argv[2]);
    uint8_t blue = atoi(argv[3]);
    uint8_t brightness = atoi(argv[4]);

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

    PixelArray pixels(Pixel(red, green, blue, brightness), 8);

    asio::io_context io;
    Blinkt blinkt(io);

    blinkt.show(pixels);

    io.run_one();

    return 0;
}