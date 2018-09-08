#include <stdint.h>
#include <iostream>
#include <string>
#include <linux/types.h>
#include <unistd.h>  // usleep
#include <stdlib.h>
#include "pixel.h"
#include "blinkt.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Running Blinkt Test Script" << endl;

    // Initialises wiringPi and uses the BCM pin numbering scheme
    if(wiringPiSetupGpio() == -1)
    {
        cout << "Failed to initialise WiringPi" << endl;
        return -1;
    }
    else
    {
        cout << "WiringPi correctly initialised" << endl;
    }
    
    Blinkt& blinkt = Blinkt::Instance();
    
    Pixel myPixel = Pixel(255,255,255);
    uint32_t red = 0xFF000003;               // hex codes fit in neatly, of course
    uint32_t green = 0x00FF003;
    uint32_t blue = 0x0000FF03;
    uint32_t white = 0b11111111111111111111111100000011; // Last 0ctet takes APA framing and brightness
    
    setPixel(blinkt, blue);    // default position is Pixel 0
    setPixel(blinkt, blue+green, 1); // Pixels can be set by number
    setPixel(blinkt, 0b00000000111111110000000000000111, 2);
    setPixel(blinkt, green + red, 3);
    setPixel(blinkt, red, 4);
    setPixel(blinkt, myPixel.getPixel(), 5);  // pre-defined Pixels can be used to set values
    setPixel(blinkt, white, 6);
    setPixel(blinkt, myPixel, 7);  // pre-defined Pixels can be used to set values

    blinkt.show();
    usleep(2000000);
    
    Blinkt& AllWhite = Blinkt::Instance();
    for (int i = 0; i < 8; i++)
        { setPixel(AllWhite, white, i); }

    AllWhite.show();
    usleep(1000000);
    
    Blinkt& AllBlack = Blinkt::Instance();

    for (int i = 0; i < 8; i++)
        { setPixel(AllBlack, 0, i); }

    AllBlack.show();
    usleep(1000000);

    Blinkt& AllRed = Blinkt::Instance();

    for (int i = 0; i < 8; i++)
        { setPixel(AllRed, red, i); }

    AllRed.show();
    usleep(1000000);

    for (int i = 0; i < 8; i++)
        { setPixel(AllBlack, 0, i); }

    AllBlack.show();
    usleep(1000000);

    return 0;	
}