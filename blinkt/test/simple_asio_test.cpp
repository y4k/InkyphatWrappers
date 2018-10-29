#include <iostream>

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
  asio::executor_work_guard<asio::io_context::executor_type> guard(
      io.get_executor());

  Blinkt blinkt(io);

  for (int i = 0; i < NUM_PIXELS; i++)
  {
    blinkt.set_pixel(255, 0, 0, DEFAULT_BRIGHTNESS, i);
  }
  blinkt.show();

  io.run();

  return 0;
}