#ifndef BLINKT_H
#define BLINKT_H

#include <iostream>
#include <mutex>
#include <unistd.h>   // usleep
#include <vector>

#include "pixel.h"    // Pixel classes

#include "blinktConstants.h"

#include <wiringPi.h>

using namespace std;

class Blinkt
{
	public:
		static Blinkt& Instance()
		{
			static Blinkt instance;
			return instance;
		}
		Blinkt(Blinkt const &) = delete;
		void operator=(Blinkt const &) = delete;

		~Blinkt(void);
		uint32_t getPixel(int p);
        int vectorLength = 13;
        void show();
        void fade(int millisecs = 500);
        void rise(int millisecs = 500, int brightnesss = 3);   //! arbitrary number
        void crossfade(Blinkt& otherParent, int steps = 5);      //! more arbitrary numbers

		void setP(uint32_t pixel, int x = 0);
        void setP(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x = 0);
        void setFullPixel(uint32_t pixel, int x);

		void writeByte(uint8_t byte);
		void flushBuffer(int length = NUM_LEDS);

	  private:
        Blinkt(void); // Private constructor ensures singleton operation
        mutex _lock; // Mutex for thread safety
        std::vector<Pixel> pVector; // Vector of pixels

		uint8_t _mosi_pin = MOSI;
		uint8_t _sclk_pin = SCLK;
};

inline void setPixel(Blinkt& blinkt, uint32_t p = 7, int x = 0)
{
	blinkt.setP(p, x);
}

inline void setPixel(Blinkt& blinkt, Pixel& p, int x = 0)
{
	uint32_t pixelValue = p.getPixel();
	setPixel(blinkt, pixelValue, x);
}

#endif