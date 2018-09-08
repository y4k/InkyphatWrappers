// Include Guard
#ifndef INKYPHAT_H
#define INKYPHAT_H

#include <stdint.h>
#include <vector>
#include <string>
#include <mutex>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "inkyphatConstants.h"

using namespace std;

class InkyPhat
{
    public:
        static InkyPhat& Instance() // Singleton accessor method - Thread safe in C++11
        {
            static InkyPhat instance;
            return instance;
        }
        InkyPhat(InkyPhat const &) = delete; // Removed method
        void operator=(InkyPhat const &) = delete; // Removed method
        
        ~InkyPhat(); // Destructor
        int update();
        int set_pixel(int row, int column, uint8_t value);
        string print_current_buffer();

    private:
        InkyPhat(); // Private constructor ensures singleton operation
        mutex _lock; // Mutex for thread safety

        int inky_version = 2;
        uint8_t colour;
        int width = WIDTH;
        int height = HEIGHT;

        vector< vector< uint8_t > > buffer;
        uint8_t command_pin = COMMAND_PIN;
        uint8_t reset_pin = RESET_PIN;
        uint8_t busy_pin = BUSY_PIN;
        uint8_t cs_pin = CS0_PIN;
            
        uint8_t border = 0b00000000;
        vector< uint8_t > palette;

        int _display_init();
        int _display_update(vector<uint8_t> buf_black, vector<uint8_t> buf_red);
        int _display_fini();
        int _busy_wait();
        int reset();
        int _send_command(uint8_t command);
        int _send_command(uint8_t command, uint8_t data);
        int _send_command(uint8_t command, vector<uint8_t> data);
        int _send_command(vector< uint8_t > command, vector< uint8_t > data);
        int _send_data(vector< uint8_t > data);
        int _spi_write(uint8_t level, vector< uint8_t > data);
};

#endif