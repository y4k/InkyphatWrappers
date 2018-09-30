#include "skywriterConstants.hpp"

#include <iostream>

#include <asio.hpp>

#include <wiringPi.h>
#include <wiringPiI2C.h>

Header parse_header(char[] bytes);

class Skywriter
{
    public:
        static Skywriter& Instance()
        {
            static Skywriter instance;
            return instance;
        }
        Skywriter(Skywriter const &) = delete;
        void operator=(Skywriter const &) = delete;
        ~Skywriter();

      private:
        Skywriter();
        static void trfr_callback_falling();
        static void trfr_callback_rising();

        void start_transfer();
        void complete_transfer();

        int _i2cFileHandler;
};