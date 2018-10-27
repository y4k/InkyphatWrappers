#include "blinkt.hpp"

Blinkt::Blinkt()
{
    for (int i = 0; i < 8; i++)
    {
        pVector.push_back(Pixel());
    }

#ifdef DEBUG
    std::cout << std::endl
              << "Pin Setup" << std::endl;

    // Setup the MOSI pin
    std::cout << "   -> MOSI pin:" << unsigned(_mosi_pin) << std::endl;
    // Set as an output pin
    std::cout << "      Mode:" << OUTPUT << std::endl;
#endif
    pinMode(_mosi_pin, OUTPUT);
    // Set the initial state to LOW
#ifdef DEBUG
    std::cout << "      InitialState:" << LOW << std::endl;
#endif
    digitalWrite(_mosi_pin, LOW);

#ifdef DEBUG
    // Setup the SCLK pin
    std::cout << "   -> SCLK pin:" << unsigned(SCLK) << endl;
    // Set as an output pin
    std::cout << "      Mode:" << OUTPUT << std::endl;
#endif
    pinMode(_sclk_pin, OUTPUT);
#ifdef DEBUG
    // Set the initial state to LOW
    std::cout << "      InitialState:" << LOW << std::endl;
#endif
    digitalWrite(_sclk_pin, LOW);
}

Blinkt::~Blinkt() {}

uint32_t Blinkt::get_pixel(int p)
{
    return pVector[p].get_pixel();
}

void Blinkt::fade(int millisecs)
{
    //!! check brightness of each pixel
    int uInterval = (millisecs)*1000;
    uint8_t fadeBr;
    uint8_t minBr;

    for (int i = 0; i < 7; i++)
    {
        //!! arbitrary j
        for (int j = 0; j < 8; j++)
        {
            fadeBr = pVector[j].get_brightness();
            if (fadeBr > 0)
            {
                fadeBr -= 1;
            }
            minBr += fadeBr;
            pVector[j].set_brightness(fadeBr);
        }

        show();
        usleep(uInterval);
        if (minBr == 0)
        {
            break;
        }
        minBr = 0;
    }
}

void Blinkt::rise(int millisecs, int brightness)
{
    int uInterval = (millisecs * 1000);
    for (int i = 0; i < brightness; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            pVector[j].set_brightness(i + 1);
        }
        show();
        usleep(uInterval);
    }
}

void Blinkt::crossfade(Blinkt &otherParent, int steps)
{
    for (int i = 0; i < steps; i++)
    {
        for (int j = 0; j < NUM_LEDS; j++)
        {
            uint8_t myRed = pVector[j].get_pixel() >> 24; // should have getRed() as a method - someone should write that.  Me.
            uint8_t myGreen = pVector[j].get_pixel() >> 16;
            uint8_t myBlue = pVector[j].get_pixel() >> 8;
            uint8_t myBright = pVector[j].get_pixel() & 0b00000111;

            uint8_t otherRed = otherParent.get_pixel(j) >> 24;
            uint8_t otherGreen = otherParent.get_pixel(j) >> 16;
            uint8_t otherBlue = otherParent.get_pixel(j) >> 8;
            uint8_t otherBright = otherParent.get_pixel(j) & 0b00000111;

            int sign;
            sign = myRed > otherRed ? -1 : 1;
            myRed += sign * (std::abs(otherRed - myRed) / (steps - i));
            sign = myGreen > otherGreen ? -1 : 1;
            myGreen += sign * std::abs(otherGreen - myGreen) / (steps - i);
            sign = myBlue > otherBlue ? -1 : 1;
            myBlue += sign * std::abs(otherBlue - myBlue) / (steps - i);

            if (myBright > otherBright) // need a method that takes into account steps and granularity
            {
                myBright--;
            }
            else if (myBright < otherBright)
            {
                myBright++;
            }

            set_pixel(myRed, myGreen, myBlue, myBright, j);
        }
        show();
        usleep(1000000 / steps);
    }
}

void Blinkt::set_pixel(uint32_t colourInfo, int x)
{
    Pixel temp = pVector[x];
    temp.set_pixel(colourInfo);
    pVector[x] = temp;
}

void Blinkt::set_full_pixel(uint32_t colourInfo, int x)
{
    Pixel temp = pVector[x];
    temp.set_pixel(colourInfo);
    pVector[x] = temp;
}

void Blinkt::set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x)
{
    Pixel temp = pVector[x];
    temp.set_pixel(r, g, b, br);
    pVector[x] = temp;
}

void Blinkt::show()
{
    write_byte(0);
    write_byte(0);
    write_byte(0);
    write_byte(0); // ensure clear buffer

    for (int n = 0; n < NUM_LEDS; n++)
    {
        write_byte(APA_SOF | (pVector[n].get_pixel() & 0b11111));
        write_byte(pVector[n].get_pixel() >> 8 & 0xFF);
        write_byte(pVector[n].get_pixel() >> 16 & 0xFF);
        write_byte(pVector[n].get_pixel() >> 24 & 0xFF);

        // increment count
    }
    flush_buffer();
}

void Blinkt::write_byte(uint8_t byte)
{
    int n;
    for (n = 0; n < 8; n++)
    {
        // bcm2835_gpio_write(MOSI, (byte & (1 << (7-n))) > 0);
        digitalWrite(_mosi_pin, (byte & (1 << (7 - n))) > 0);
        // bcm2835_gpio_write(SCLK, HIGH);
        digitalWrite(_sclk_pin, HIGH);
        // bcm2835_gpio_write(SCLK, LOW);
        digitalWrite(_sclk_pin, LOW);
    }
}

void Blinkt::flush_buffer(int length)
{
    /*
    ASA_SOF LED string does not need precise timing but the payback for that
    is having to pass in clock timings. The documentation is spectacularly
    unhelpful in how to do this.  However, writing several blank bytes flushes
    the buffer that is held within the LED array/string. This function flushes
    the buffer, and can be over-ridden in size to flush longer buffers for
    longer strings. Default length is NUM_LEDS
  */
    for (int i = 0; i < (length / 2) + 1; i++) // initial guess at length of buffer needed
    {
        write_byte(0);
    }
}