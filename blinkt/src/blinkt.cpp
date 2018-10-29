#include "blinkt.hpp"

Blinkt::Blinkt(asio::io_context &io, int numPixels) : mIo{io}, mNumPixels{numPixels}
{
#ifdef DEBUG
  std::cout << std::endl
            << "Pin Setup" << std::endl;

  // Setup the MOSI pin
  std::cout << "   -> MOSI pin:" << unsigned(mMosiPin) << std::endl;
  // Set as an output pin
  std::cout << "      Mode:" << OUTPUT << std::endl;
#endif
  pinMode(mMosiPin, OUTPUT);
  // Set the initial state to LOW
#ifdef DEBUG
  std::cout << "      InitialState:" << LOW << std::endl;
#endif
  digitalWrite(mMosiPin, LOW);

#ifdef DEBUG
  // Setup the SCLK pin
  std::cout << "   -> SCLK pin:" << unsigned(SCLK) << endl;
  // Set as an output pin
  std::cout << "      Mode:" << OUTPUT << std::endl;
#endif
  pinMode(mSclkPin, OUTPUT);
#ifdef DEBUG
  // Set the initial state to LOW
  std::cout << "      InitialState:" << LOW << std::endl;
#endif
  digitalWrite(mSclkPin, LOW);
}

Blinkt::~Blinkt() {}

asio::io_context &Blinkt::get_io_context() { return mIo; }

void Blinkt::fade(PixelArray pixelArray, int millisecs)
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
      fadeBr = pixelArray[j].get_brightness();
      if (fadeBr > 0)
      {
        fadeBr -= 1;
      }
      minBr += fadeBr;
      pixelArray[j].set_brightness(fadeBr);
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

void Blinkt::rise(PixelArray array, int millisecs)
{
  int uInterval = (millisecs * 1000);
  for (int i = 0; i < array.brightness; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      array[j].set_brightness(i + 1);
    }
    show(array);
    usleep(uInterval);
  }
}

void Blinkt::crossfade(PixelArray toArray, int steps)
{
  PixelArray fromArray(mNumPixels);
  crossfade(fromArray, toArray, millisecs);
}

void Blinkt::crossfade(PixelArray fromArray, PixelArray toArray, int steps)
{
  for (int i = 0; i < steps; i++)
  {
    for (int j = 0; j < NUM_PIXELS; j++)
    {
      uint8_t myRed = pVector[j].get_pixel_color() >> 24; // should have getRed() as a method - someone should write that.  Me.
      uint8_t myGreen = pVector[j].get_pixel_color() >> 16;
      uint8_t myBlue = pVector[j].get_pixel_color() >> 8;
      uint8_t myBright = pVector[j].get_pixel_color() & 0b00000111;

      uint8_t otherRed = otherParent.get_pixel_color(j) >> 24;
      uint8_t otherGreen = otherParent.get_pixel_color(j) >> 16;
      uint8_t otherBlue = otherParent.get_pixel_color(j) >> 8;
      uint8_t otherBright = otherParent.get_pixel_color(j) & 0b00000111;

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

void Blinkt::show(PixelArray array)
{
  write_byte(0);
  write_byte(0);
  write_byte(0);
  write_byte(0); // ensure clear buffer

  for (int n = 0; n < NUM_PIXELS; n++)
  {
    write_byte(APA_SOF | (array[n].get_pixel_color() & 0b11111));
    write_byte(array[n].get_pixel_color() >> 8 & 0xFF);
    write_byte(array[n].get_pixel_color() >> 16 & 0xFF);
    write_byte(array[n].get_pixel_color() >> 24 & 0xFF);

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
    digitalWrite(mMosiPin, (byte & (1 << (7 - n))) > 0);
    // bcm2835_gpio_write(SCLK, HIGH);
    digitalWrite(mSclkPin, HIGH);
    // bcm2835_gpio_write(SCLK, LOW);
    digitalWrite(mSclkPin, LOW);
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
    longer strings. Default length is NUM_PIXELS
  */
  for (int i = 0; i < (length / 2) + 1; i++) // initial guess at length of buffer needed
  {
    write_byte(0);
  }
}