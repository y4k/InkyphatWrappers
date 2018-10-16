#include "skywriterConstants.hpp"
#include "skywriter.hpp"

int main(void)
{
    // sets up the wiringPi library
    if (wiringPiSetupGpio() < 0)
    {
        fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
        return 1;
    }

    Skywriter &sw = Skywriter::Instance();

    while (1)
    {
        delay(100); // wait 100 millisecond
    }

    return 0;
}