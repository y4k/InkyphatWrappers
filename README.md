# InkyphatWrappers

## Overview

Wrappers for:

1) [Inkyphat](https://shop.pimoroni.com/products/inky-phat) from [Pimoroni](https://shop.pimoroni.com/)
2) [Blinkt](https://shop.pimoroni.com/products/blinkt) from [Pimoroni](https://shop.pimoroni.com/)
3) [JoyBonnet](https://shop.pimoroni.com/products/adafruit-joy-bonnet-for-raspberry-pi) from [Adafruit](https://www.adafruit.com/product/3464)
4) [Skywriter](https://shop.pimoroni.com/products/skywriter) from [Pimoroni](https://shop.pimoroni.com)

When used on a Raspberry Pi, requires the [wiringPi library](http://wiringpi.com/download-and-install/)

Requires the SPI interface to be enabled in order to run InkyPhat on a Raspberry Pi. Will also require either running with root access or by adding the desired user to the ```gpio``` and ```spi``` groups.

```bash
sudo adduser <username> gpio
sudo adduser <username> spi
```

## Example Usage

### Setup WiringPi

```cpp
// Initialises wiringPi and uses the BCM pin numbering scheme
if(wiringPiSetupGpio() == -1)
{
    cout << "Failed to initialise WiringPi" << endl;
    return -1;
}
else
{
    cout << "WiringPi correctly initialised" << endl;
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

setPixel(blinkt, myPixel.getPixel(), 6);        // Pre-defined Pixels can be used to set values
setPixel(blinkt, myPixel, 7);                   // Pre-defined Pixels can be used to set values
```

#### InkyPhat

InkyPhat requires both WiringPi and the SPI interface to be initialised.

```cpp
// Initialises wiringPi and uses the BCM pin numbering scheme
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
if(wiringPiSPISetup(CS0_PIN, 488000) == -1)
{
    cout << "Could not initialise WiringPi SPI library" << endl;
    return -1;
}
else
{
    cout << "WiringPi SPI library initialised" << endl;
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