#include <iostream>
#include <functional>

#include <asio.hpp>

#include "pixel.hpp"
#include "blinkt.hpp"

int main(void)
{
  std::cout << "Simple Asio service test" << std::endl;

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
  // asio::executor_work_guard<asio::io_context::executor_type> guard(
  //     io.get_executor());

  Blinkt blinkt(io);

  PixelArray pixels(NUM_PIXELS);

  uint8_t br = 0;

  pixels[0].set_full_color(5, 0, 0, br);  // Red
  pixels[1].set_full_color(5, 0, 0, br);  // Green
  pixels[2].set_full_color(5, 0, 0, br);  // Blue
  pixels[3].set_full_color(5, 0, 0, br);  // Red
  pixels[4].set_full_color(5, 0, 0, br);  // Green
  pixels[5].set_full_color(5, 0, 0, br); // Blue
  pixels[6].set_full_color(5, 0, 0, br); // Red
  pixels[7].set_full_color(5, 0, 0, br); // Green

  asio::steady_timer timer(io, asio::chrono::seconds(1));

  std::cout << "Showing 0 brightness" << std::endl;
  blinkt.show(pixels);
  io.run_one();

  timer.wait();

  for(int count = 1;count < 32;count++)
  {
    br = count;
    for(int i = 0;i < 8;i++)
    {
      pixels[i].set_brightness(br);
    }

    std::cout << "Showing " << unsigned(br) << " brightness" << std::endl;
    blinkt.show(pixels);
    io.restart();
    io.run_one();

    timer.expires_after(asio::chrono::seconds(1));
    timer.wait();
  }

  std::cout << "Done" << std::endl;

  return 0;
}
