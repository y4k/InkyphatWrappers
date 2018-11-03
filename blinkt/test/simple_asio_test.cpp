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

  pixels[0].set_full_color(255, 0, 0, 0);  // Red
  pixels[1].set_full_color(0, 255, 0, 2);  // Green
  pixels[2].set_full_color(0, 0, 255, 4);  // Blue
  pixels[3].set_full_color(255, 0, 0, 6);  // Red
  pixels[4].set_full_color(0, 255, 0, 8);  // Green
  pixels[5].set_full_color(0, 0, 255, 10); // Blue
  pixels[6].set_full_color(255, 0, 0, 12); // Red
  pixels[7].set_full_color(0, 255, 0, 14); // Green

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