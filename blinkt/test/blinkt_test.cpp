#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <unistd.h> // usleep

#include <linux/types.h>
#include <asio.hpp>

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

  asio::io_context io;
  asio::executor_work_guard<asio::io_context::executor_type> guard(
      io.get_executor());

  Blinkt blinkt(io);

  Pixel myPixel = Pixel(255, 0, 0, 2);
  uint32_t red = 0xFF000003; // hex codes fit in neatly, of course
  uint32_t green = 0x00FF003;
  uint32_t blue = 0x0000FF03;
  uint32_t white = 0b11111111111111111111111100000011; // Last Octet takes APA framing and brightness

  for (int i = 0; i < NUM_PIXELS; i++)
  {
    set_pixel(blinkt, myPixel, i);
  }
  blinkt.show();

  usleep(3000000);

  set_pixel(blinkt, blue);            // default position is Pixel 0
  set_pixel(blinkt, blue + green, 1); // Pixels can be set by number
  set_pixel(blinkt, green, 2);
  set_pixel(blinkt, green + red, 3);
  set_pixel(blinkt, red, 4);
  set_pixel(blinkt, myPixel.get_pixel_color(), 5); // pre-defined Pixels can be used to set values
  set_pixel(blinkt, white, 6);
  set_pixel(blinkt, myPixel, 7); // pre-defined Pixels can be used to set values

  std::cout << "Displaying:" << std::endl
            << "Blue|Blue+Green|Green|Green+Red|Red|White|White"
            << std::endl;

  blinkt.show();
  usleep(2000000);

  for (int i = 0; i < 8; i++)
  {
    set_pixel(blinkt, white, i);
  }

  std::cout << "Displaying:" << std::endl
            << "All White"
            << std::endl;

  blinkt.show();
  usleep(1000000);

  for (int i = 0; i < 8; i++)
  {
    set_pixel(blinkt, 0, i);
  }

  std::cout << "Displaying:" << std::endl
            << "Nothing"
            << std::endl;

  blinkt.show();
  usleep(1000000);

  for (int i = 0; i < 8; i++)
  {
    set_pixel(blinkt, red, i);
  }

  std::cout << "Displaying:" << std::endl
            << "All Red with fade"
            << std::endl;

  blinkt.show();
  usleep(1000000);
  blinkt.fade(2000);

  for (int i = 0; i < 8; i++)
  {
    set_pixel(blinkt, 0, i);
  }

  std::cout << "Displaying:" << std::endl
            << "Nothing"
            << std::endl;

  blinkt.show();
  usleep(1000000);

  std::cout << "End" << std::endl;

  io.run();
  return 0;
}