#ifndef BLINKT_H
#define BLINKT_H

#include <iostream>
#include <mutex>
#include <unistd.h> // usleep
#include <vector>

#include "pixel.hpp" // Pixel classes

#include "blinkt_constants.hpp"

#include <wiringPi.h>

class Blinkt
{
  public:
	static Blinkt &Instance()
	{
		static Blinkt instance;
		return instance;
	}
	Blinkt(Blinkt const &) = delete;
	void operator=(Blinkt const &) = delete;

	~Blinkt(void);
	uint32_t get_pixel(int p);
	int vectorLength = 13;
	void show();
	void fade(int millisecs = 500);
	void rise(int millisecs = 500, int brightnesss = 3); //! arbitrary number
	void crossfade(Blinkt &otherParent, int steps = 5);  //! more arbitrary numbers

	void set_pixel(uint32_t pixel, int x = 0);
	void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t br, int x = 0);
	void set_full_pixel(uint32_t pixel, int x);

	void write_byte(uint8_t byte);
	void flush_buffer(int length = NUM_LEDS);

  private:
	Blinkt(void);				// Private constructor ensures singleton operation
	std::mutex _lock;			// Mutex for thread safety
	std::vector<Pixel> pVector; // Vector of pixels

	uint8_t _mosi_pin = MOSI;
	uint8_t _sclk_pin = SCLK;
};

inline void setPixel(Blinkt &blinkt, uint32_t p = 7, int x = 0)
{
	blinkt.set_pixel(p, x);
}

inline void setPixel(Blinkt &blinkt, Pixel &p, int x = 0)
{
	uint32_t pixelValue = p.get_pixel();
	setPixel(blinkt, pixelValue, x);
}

#endif