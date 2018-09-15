#ifndef JOY_BONNET_H
#define JOY_BONNET_H

#include "joyBonnetConstants.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std;

enum JoystickDirection
{
    NONE = 0,
    UP = 1,
    DOWN = 2,
    RIGHT = 4,
    UP_RIGHT = 5,
    DOWN_RIGHT = 6,
    LEFT = 8,
    UP_LEFT = 9,
    DOWN_LEFT = 10
};

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
        ~JoyBonnet(){} // Destructor

        static void x_callback(void);
        static void y_callback(void);
        static void a_callback(void);
        static void b_callback(void);
        static void start_callback(void);
        static void select_callback(void);
        static void p1_callback(void);
        static void p2_callback(void);

        void addHandler(int pin, const function<void()> callback);

        int read_joystick_x();
        int read_joystick_y();

        JoystickDirection read_joystick_direction();

      private:
        int read_joystick(int channel);
        JoyBonnet();// Private constructor ensures singleton operation
        void execute_callbacks(int pin);
        map< int, vector<function<void()> > > _callbacks;
        int _i2cFileHandler;

        int _channels[4] =
            {
                ADS1015_REG_CONFIG_MUX_SINGLE_0,
                ADS1015_REG_CONFIG_MUX_SINGLE_1,
                ADS1015_REG_CONFIG_MUX_SINGLE_2,
                ADS1015_REG_CONFIG_MUX_SINGLE_3
            };
};

#endif