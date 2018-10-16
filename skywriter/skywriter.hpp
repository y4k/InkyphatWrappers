#include "skywriterConstants.hpp"

#include <iostream>
#include <unistd.h>
#include <errno.h>

#include <asio.hpp>

#include <wiringPi.h>
#include <wiringPiI2C.h>

Header parse_header(char bytes[]);
void parse_sensor_data_output(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t *payload);
void parse_system_status(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t *payload);
void parse_fw_info(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t *payload);
void print_header(uint8_t msgSize, uint8_t sequence, uint8_t id);
int combine_bytes(int numBytes, uint8_t *bytes);

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

        static void xfr_callback_falling();
        static void xfr_callback_rising();

        asio::thread* _worker_thread;
        asio::io_context _io;
        asio::executor_work_guard<asio::io_context::executor_type> _guard;

        void start_process();
        void end_process();

        void start_transfer();
        void complete_transfer();

        void read_once();

        void reset();

        int _i2cFileHandler;
};