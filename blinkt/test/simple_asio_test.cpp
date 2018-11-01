#include <iostream>
#include <functional>

#include <asio.hpp>

#include "pixel.hpp"
#include "blinkt.hpp"

void show_pixels(asio::steady_timer &timer, Blinkt &blinkt, PixelArray &pixels, const std::error_code &code);
void off_pixels(asio::steady_timer &timer, Blinkt &blinkt, PixelArray &pixels, const std::error_code &code);

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

  for (int i = 0; i < NUM_PIXELS; i++)
  {
    pixels[i].set_pixel(255, 0, 0, DEFAULT_BRIGHTNESS);
  }
  blinkt.show(pixels);

  asio::steady_timer timer(io, asio::chrono::seconds(5));

  timer.async_wait([&](const std::error_code &code) { show_pixels(timer, blinkt, pixels, code); });

  io.run();

  return 0;
}

void show_pixels(asio::steady_timer &timer, Blinkt &blinkt, PixelArray &pixels, const std::error_code &code)
{
  blinkt.show(pixels);
  timer.expires_after(asio::chrono::seconds(5));
  timer.async_wait([&](const std::error_code &code) { off_pixels(timer, blinkt, pixels, code); });
}

void off_pixels(asio::steady_timer &timer, Blinkt &blinkt, PixelArray &pixels, const std::error_code &code)
{
  blinkt.off();
  timer.expires_after(asio::chrono::seconds(5));
  timer.async_wait([&](const std::error_code &code) { show_pixels(timer, blinkt, pixels, code); });
}