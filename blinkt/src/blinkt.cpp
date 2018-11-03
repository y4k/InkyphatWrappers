#include "blinkt.hpp"

Blinkt::Blinkt(asio::io_context &io) : mIo{io}
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
  std::cout << "   -> SCLK pin:" << unsigned(SCLK) << std::endl;
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

void Blinkt::update(PixelArray array)
{
  // Start of frame
  write_byte(0b00000000);
  write_byte(0b00000000);
  write_byte(0b00000000);
  write_byte(0b00000000);

  // LED frames - one per LED
  for (int n = 0; n < array.size(); n++)
  {
    Pixel const &pixel = array[n];
    write_byte(APA_SOF | pixel.get_brightness());
    write_byte(pixel.get_blue());
    write_byte(pixel.get_green());
    write_byte(pixel.get_red());
  }

  // End of frame
  write_byte(0b11111111);
  write_byte(0b11111111);
  write_byte(0b11111111);
  write_byte(0b11111111);

  // flush_buffer(NUM_PIXELS);
}

void Blinkt::show(PixelArray array)
{
  asio::post(mIo, [=]() { update(array); });
}

void Blinkt::off()
{
  PixelArray pixels(8);
  Blinkt::show(pixels);
}

void Blinkt::fade(PixelArray array, asio::chrono::milliseconds timeout)
{
  // Minimum 10ms intervals
  int intervals = timeout / asio::chrono::milliseconds(10);

  if (intervals < 1)
  {
    intervals = 1;
  }

  uint8_t fadeBr;
  uint8_t minBr;

  for (int i = 0; i < intervals; i++)
  {
    for (int j = 0; j < array.size(); j++)
    {
      fadeBr = array[j].get_brightness();
      if (fadeBr > 0)
      {
        fadeBr -= 1;
      }
      minBr += fadeBr;
      array[j].set_brightness(fadeBr);
    }

    update(array);
  }
}

// void Blinkt::rise(PixelArray array, int millisecs)
// {
//   int uInterval = (millisecs * 1000);
//   for (int i = 0; i < array.brightness; i++)
//   {
//     for (int j = 0; j < 8; j++)
//     {
//       array[j].set_brightness(i + 1);
//     }
//     show(array);
//     usleep(uInterval);
//   }
// }

// void Blinkt::crossfade(PixelArray toArray, int steps)
// {
//   PixelArray fromArray(mNumPixels);
//   crossfade(fromArray, toArray, millisecs);
// }

// void Blinkt::crossfade(PixelArray fromArray, PixelArray toArray, int steps)
// {
//   for (int i = 0; i < steps; i++)
//   {
//     for (int j = 0; j < NUM_PIXELS; j++)
//     {
//       uint8_t myRed = pVector[j].get_pixel_color() >> 24; // should have getRed() as a method - someone should write that.  Me.
//       uint8_t myGreen = pVector[j].get_pixel_color() >> 16;
//       uint8_t myBlue = pVector[j].get_pixel_color() >> 8;
//       uint8_t myBright = pVector[j].get_pixel_color() & 0b00000111;

//       uint8_t otherRed = otherParent.get_pixel_color(j) >> 24;
//       uint8_t otherGreen = otherParent.get_pixel_color(j) >> 16;
//       uint8_t otherBlue = otherParent.get_pixel_color(j) >> 8;
//       uint8_t otherBright = otherParent.get_pixel_color(j) & 0b00000111;

//       int sign;
//       sign = myRed > otherRed ? -1 : 1;
//       myRed += sign * (std::abs(otherRed - myRed) / (steps - i));
//       sign = myGreen > otherGreen ? -1 : 1;
//       myGreen += sign * std::abs(otherGreen - myGreen) / (steps - i);
//       sign = myBlue > otherBlue ? -1 : 1;
//       myBlue += sign * std::abs(otherBlue - myBlue) / (steps - i);

//       if (myBright > otherBright) // need a method that takes into account steps and granularity
//       {
//         myBright--;
//       }
//       else if (myBright < otherBright)
//       {
//         myBright++;
//       }

//       set_pixel(myRed, myGreen, myBlue, myBright, j);
//     }
//     show();
//     usleep(1000000 / steps);
//   }
// }

void Blinkt::write_byte(uint8_t byte)
{
  for (int n = 0; n < 8; n++)
  {
    digitalWrite(mMosiPin, (byte & (1 << (7 - n))) > 0);
    digitalWrite(mSclkPin, HIGH);
    digitalWrite(mSclkPin, LOW);
  }
}