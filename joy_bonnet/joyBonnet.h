#ifndef JOY_BONNET_H
#define JOY_BONNET_H

#include "joyBonnetConstants.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <functional>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <tuple>
#include <mutex>
#include <chrono>

#include <asio.hpp>

#include <wiringPi.h>
#include <wiringPiI2C.h>

enum JoystickDirection
{
    NONE = -1,
    UP = 0,
    UP_RIGHT = 1,
    RIGHT = 2,
    DOWN_RIGHT = 3,
    DOWN = 4,
    DOWN_LEFT = 5,
    LEFT = 6,
    UP_LEFT = 7,
};

int check_top_right_quadrant(int x, int y);
std::string print_direction(JoystickDirection direction);
std::string get_pin_name(int pin);

class JoyBonnet
{
    public:
        static JoyBonnet& Instance()
        {
            static JoyBonnet instance;
            return instance;
        }
        JoyBonnet(JoyBonnet const &) = delete; // Removed method
        void operator=(JoyBonnet const &) = delete; // Removed method
        ~JoyBonnet(); // Destructor

        void addHandler(int pin, const std::function<void()> callback);

        std::tuple<int, int> read_joystick_coords();
        int read_joystick_x();
        int read_joystick_y();

        JoystickDirection read_joystick_direction();

    private:
        int read_joystick(int channel);
        JoyBonnet();// Private constructor ensures singleton operation

        void execute_callbacks(int pin, const asio::error_code& e);

        // ASIO
        std::chrono::milliseconds _time_out;
        asio::io_context _io;
        asio::thread* _worker_thread;
        asio::executor_work_guard<asio::io_context::executor_type> _guard;

        // Timers
        asio::steady_timer _x_timer;

        static void x_callback_rising(void);
        static void x_callback_falling(void);
        static void y_callback_rising(void);
        static void y_callback_falling(void);
        static void a_callback_rising(void);
        static void a_callback_falling(void);
        static void b_callback_rising(void);
        static void b_callback_falling(void);
        static void start_callback_rising(void);
        static void start_callback_falling(void);
        static void select_callback_rising(void);
        static void select_callback_falling(void);
        static void p1_callback_rising(void);
        static void p1_callback_falling(void);
        static void p2_callback_rising(void);
        static void p2_callback_falling(void);

        std::map< int, std::vector<std::function<void()> > > _callbacks;

        int _i2cFileHandler;

        std::mutex _callback_lock;
        std::mutex _joystick_lock;

        int _channels[4] =
            {
                ADS1015_REG_CONFIG_MUX_SINGLE_0,
                ADS1015_REG_CONFIG_MUX_SINGLE_1,
                ADS1015_REG_CONFIG_MUX_SINGLE_2,
                ADS1015_REG_CONFIG_MUX_SINGLE_3
            };
};

#endif