#include "skywriter.hpp"
#include "skywriterConstants.hpp"

int main(void)
{
  // sets up the wiringPi library
  if (wiringPiSetupGpio() < 0)
  {
    fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
    return 1;
  }

  asio::io_context io;
  asio::executor_work_guard<asio::io_context::executor_type> guard(
      io.get_executor());

  Skywriter &sw = new Skywriter(io);

  io.run();

  return 0;
}