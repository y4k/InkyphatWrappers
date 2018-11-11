# Raspberry Pi GPIO Component Drivers

This repository includes libraries for the use of a number of different HATS, pHATS and general components with a Raspberry Pi or PiZero. They are writtten in C++ and upfront I will say that
this is mostly a project for my self to learn C++, explore more about the Pi and these components. Anyone willing to take a chance on using these libraries should understand that. I've endeavoured
to get them to in a functional state and where possible, even write some documentation about what I intended.

Anyone reading this that has any comments that they wish to share or any problems using the libraries, please feel free to let me know.

## Overview

Libraries for:

1. [Inkyphat](https://shop.pimoroni.com/products/inky-phat) from [Pimoroni](https://shop.pimoroni.com/)
2. [Blinkt](https://shop.pimoroni.com/products/blinkt) from [Pimoroni](https://shop.pimoroni.com/)
3. [JoyBonnet](https://shop.pimoroni.com/products/adafruit-joy-bonnet-for-raspberry-pi) from [Adafruit](https://www.adafruit.com/product/3464)
4. [Skywriter](https://shop.pimoroni.com/products/skywriter) from [Pimoroni](https://shop.pimoroni.com)

## Dependencies

The most notable dependencies are the [wiringPi library](http://wiringpi.com/download-and-install/) and [Asio](http://think-async.com/) which is used in its standalone form and so does not require
the entirety of Boost. Should the user already have Boost installed then by all means, disregard the setup used in the Makefile to use Asio as a standalone library.

Requires the SPI interface to be enabled in order to run InkyPhat on a Raspberry Pi. Will also require either running with root access or by adding the desired user to the `gpio` and `spi` groups.

```bash
sudo adduser <username> gpio
sudo adduser <username> spi
```

I use the Broadcom numbering system which is handily displayed here: [Pinout](http://pinout.xyz). Whilst wiringPi can be initialised with one of three different numbering systems, I decided to keep
my sanity by choosing one and sticking to it throughout development. In the future I will attempt to make the libraries support all three.

## Example Usage

### Setup WiringPi

```cpp
// Initialises wiringPi and uses the BCM pin numbering scheme
if(wiringPiSetupGpio() == -1)
{
    std::cout << "Failed to initialise WiringPi" << std::endl;
    return -1;
}
else
{
    std::cout << "WiringPi correctly initialised" << std::endl;
}
```

#### Blinkt

```cpp
Blinkt& blinkt = Blinkt::Instance();    // Gets a reference to the Blinkt instance

uint32_t blue = 0x0000FF03;             // Define a colour

setPixel(blinkt, blue);                 // default position is Pixel 0
setPixel(blinkt, blue, 1);              // Set position 1 to blue as well

blinkt.show();                          // Show the changes
```

Pixels can also be defined beforehand and used to update Blinkt

```cpp
Pixel myPixel = Pixel(255,255,255);             // Define a pixel

Blinkt& blinkt = Blinkt::Instance();            // Gets a reference to the Blinkt instance

setPixel(blinkt, myPixel.get_pixel(), 6);        // Pre-defined Pixels can be used to set values
setPixel(blinkt, myPixel, 7);                   // Pre-defined Pixels can be used to set values
```

#### InkyPhat

InkyPhat requires both WiringPi and the SPI interface to be initialised.

```cpp
// Initialises wiringPi and uses the BCM pin numbering scheme
if(wiringPiSetupGpio() == -1)
{
    std::cout << "Failed to initialise WiringPi" << std::endl;
    return -1;
}
else
{
    std::cout << "WiringPi correctly initialised" << std::endl;
}

// Setup spi
if(wiringPiSPISetup(CS0_PIN, 488000) == -1)
{
    std::cout << "Could not initialise WiringPi SPI library" << std::endl;
    return -1;
}
else
{
    std::cout << "WiringPi SPI library initialised" << std::endl;
}

InkyPhat& inky = InkyPhat::Instance(); // Get reference to the InkyPhat class
```

```cpp
int width = WIDTH;
int height = HEIGHT;

cout << "Display vertical lines of a given colour:" << colour << endl;
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

inky.update(); // Show the changes
```

#### JoyBonnet

#### Skywriter
