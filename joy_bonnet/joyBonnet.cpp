#include "joyBonnet.h"

JoyBonnet::JoyBonnet() :
    _time_out(100),
    _io(),
    _guard(_io.get_executor()),
    _x_timer(_io, _time_out),
    _y_timer(_io, _time_out),
    _a_timer(_io, _time_out),
    _b_timer(_io, _time_out),
    _start_timer(_io, _time_out),
    _select_timer(_io, _time_out),
    _p1_timer(_io, _time_out),
    _p2_timer(_io, _time_out)
{
    pullUpDnControl(X_BUTTON_PIN, PUD_UP);
    wiringPiISR(X_BUTTON_PIN, INT_EDGE_RISING, &x_callback_rising);
    wiringPiISR(X_BUTTON_PIN, INT_EDGE_FALLING, &x_callback_falling);
    
    pullUpDnControl(Y_BUTTON_PIN, PUD_UP);
    wiringPiISR(Y_BUTTON_PIN, INT_EDGE_RISING, &y_callback_rising);
    wiringPiISR(Y_BUTTON_PIN, INT_EDGE_FALLING, &y_callback_falling);
    
    pullUpDnControl(A_BUTTON_PIN, PUD_UP);
    wiringPiISR(A_BUTTON_PIN, INT_EDGE_RISING, &a_callback_rising);
    wiringPiISR(A_BUTTON_PIN, INT_EDGE_FALLING, &a_callback_falling);
    
    pullUpDnControl(B_BUTTON_PIN, PUD_UP);
    wiringPiISR(B_BUTTON_PIN, INT_EDGE_RISING, &b_callback_rising);
    wiringPiISR(B_BUTTON_PIN, INT_EDGE_FALLING, &b_callback_falling);

    pullUpDnControl(START_BUTTON_PIN, PUD_UP);
    wiringPiISR(START_BUTTON_PIN, INT_EDGE_RISING, &start_callback_rising);
    wiringPiISR(START_BUTTON_PIN, INT_EDGE_FALLING, &start_callback_falling);

    pullUpDnControl(SELECT_BUTTON_PIN, PUD_UP);
    wiringPiISR(SELECT_BUTTON_PIN, INT_EDGE_RISING, &select_callback_rising);
    wiringPiISR(SELECT_BUTTON_PIN, INT_EDGE_FALLING, &select_callback_falling);
    
    pullUpDnControl(PLAYER_1_BUTTON_PIN, PUD_UP);
    wiringPiISR(PLAYER_1_BUTTON_PIN, INT_EDGE_RISING, &p1_callback_rising);
    wiringPiISR(PLAYER_1_BUTTON_PIN, INT_EDGE_FALLING, &p1_callback_falling);
    
    pullUpDnControl(PLAYER_2_BUTTON_PIN, PUD_UP);
    wiringPiISR(PLAYER_2_BUTTON_PIN, INT_EDGE_RISING, &p2_callback_rising);
    wiringPiISR(PLAYER_2_BUTTON_PIN, INT_EDGE_FALLING, &p2_callback_falling);

    // Setup i2c communication to the joystick
    if ( (_i2cFileHandler = wiringPiI2CSetup(ADS1x15_DEFAULT_ADDRESS)) == -1)
    {
        #ifdef DEBUG
        std::cout << "Wiring Pi i2c setup failed:" << strerror(errno) << std::endl;
        #endif
    }

    // Create and start the worker thread. Call run on the blocked service from that thread.
    _worker_thread = new asio::thread(
     std::bind(
       static_cast<asio::io_context::count_type (asio::io_service::*)(void)>(&asio::io_context::run),
       &_io
       )
      );

    #ifdef DEBUG
    std::cout << "Debounce time out set at " << _time_out.count() << " milliseconds" << std::endl;
    #endif
}

JoyBonnet::~JoyBonnet()
{
    _x_timer.cancel();
    _io.reset();
    _io.stop();
    _worker_thread -> join();
    delete _worker_thread;
}

// Callbacks
void JoyBonnet::x_callback_rising(void) { }

void JoyBonnet::y_callback_rising(void) { }

void JoyBonnet::a_callback_rising(void) { }

void JoyBonnet::b_callback_rising(void) { }

void JoyBonnet::start_callback_rising(void) { }

void JoyBonnet::select_callback_rising(void) { }

void JoyBonnet::p1_callback_rising(void) { }

void JoyBonnet::p2_callback_rising(void) { }

// FALLING Callbacks
void JoyBonnet::x_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._x_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._x_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(X_BUTTON_PIN, e);
            }
        );
}

void JoyBonnet::y_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._y_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._y_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(Y_BUTTON_PIN, e);
            }
        );
}

void JoyBonnet::a_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._a_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._a_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(A_BUTTON_PIN, e);
            }
        );
}
void JoyBonnet::b_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._b_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._b_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(B_BUTTON_PIN, e);
            }
        );
}
void JoyBonnet::start_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._start_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._start_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(START_BUTTON_PIN, e);
            }
        );
}
void JoyBonnet::select_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._select_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._select_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(SELECT_BUTTON_PIN, e);
            }
        );
}
void JoyBonnet::p1_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._p1_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._p1_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(PLAYER_1_BUTTON_PIN, e);
            }
        );
}
void JoyBonnet::p2_callback_falling(void)
{
    JoyBonnet &instance = JoyBonnet::Instance();
    // When a falling interrupt occurs, update the expires tim
    instance._p2_timer.expires_after(instance._time_out);
    // Setup a new async wait
    instance._p2_timer.async_wait(
            [&] ( const asio::error_code& e) {
                instance.execute_callbacks(PLAYER_2_BUTTON_PIN, e);
            }
        );
}

// Execute the callbacks for a given pin
void JoyBonnet::execute_callbacks(int pin, const asio::error_code& e)
{
    if(e != asio::error::operation_aborted)
    {
        std::lock_guard<std::mutex> lock(_callback_lock);
        #ifdef DEBUG
        std::cout << "Timer for " << get_pin_name(pin) << " expired" << std::endl;
        #endif

        auto cb = _callbacks[pin];
        for_each(cb.begin(), cb.end(), [](std::function<void()> f) { f(); });
    }
    else
    {
        #ifdef DEBUG
        std::cout << "Timer for " << get_pin_name(pin) << " has been cancelled" << std::endl;
        #endif
    }
}

void JoyBonnet::addHandler(int pin, const std::function<void()> callback)
{
    std::lock_guard<std::mutex> lock(_callback_lock);

    _callbacks[pin].push_back(callback);
}

int JoyBonnet::read_joystick(int channel)
{
    std::lock_guard<std::mutex> lock(_joystick_lock);

    int configword = ADS1015_REG_CONFIG_CQUE_NONE |
                 ADS1015_REG_CONFIG_CLAT_NONLAT |
                 ADS1015_REG_CONFIG_CPOL_ACTVLOW |
                 ADS1015_REG_CONFIG_CMODE_TRAD |
                 ADS1015_REG_CONFIG_DR_1600SPS |
                 ADS1015_REG_CONFIG_MODE_SINGLE |
                 ADS1015_REG_CONFIG_GAIN_ONE |
                 _channels[channel] |
                 ADS1015_REG_CONFIG_OS_SINGLE;

    int configdata[2] = { configword >> 8, configword & 0xFF};
    int writeBytes = configdata[0] | configdata[1] << 8;
    if (wiringPiI2CWriteReg16(_i2cFileHandler, ADS1x15_POINTER_CONFIG, writeBytes) == -1)
    {
        std::cout << "Wiring Pi Write16 Reg failed:" << strerror(errno) << std::endl;
    }

    int readValue = wiringPiI2CReadReg16(_i2cFileHandler, ADS1x15_POINTER_CONFIG);

    while (1)
    {
        readValue = wiringPiI2CReadReg16(_i2cFileHandler, ADS1x15_POINTER_CONFIG);

        if (((readValue >> 8) & 0xFF) & 0x80)
        {
            int analogdata = wiringPiI2CReadReg16(_i2cFileHandler, ADS1x15_POINTER_CONVERSION);

            analogdata = (analogdata >> 4) & 0xFFF; // Gets 12 bit value and mask it just in case

            int b1 = (analogdata >> 8);
            int b2 = (analogdata & 0xFF);

            return ((b2 << 8) | b1); // Rearrange the byte order
        }
    }
}

std::tuple<int,int> JoyBonnet::read_joystick_coords()
{
    return std::make_tuple(read_joystick_x(), read_joystick_y());
}

int JoyBonnet::read_joystick_x()
{
    return read_joystick(1) - JOYSTICK_OFFSET;
}

int JoyBonnet::read_joystick_y()
{
    return JOYSTICK_OFFSET - read_joystick(0);
}

JoystickDirection JoyBonnet::read_joystick_direction()
{
    int x = read_joystick_x();
    int y = read_joystick_y();

    int result = -1;
    if (x > 0)
    {
        if (y > 0)
        {
            result = check_top_right_quadrant(x, y);
        }
        else
        {
            result = check_top_right_quadrant(x, -y);
            if(result != -1)
            {
                result = 4 - result;
            }
        }
    }
    else
    {
        if (y < 0)
        {
            result = check_top_right_quadrant(-x, -y);
            if(result != -1)
            {
                result += 4;
            }
        }
        else
        {
            result = check_top_right_quadrant(-x, y);
            if(result != -1)
            {
                result = 8 - result;
                result %= 8;
            }
        }
    }

    return static_cast<JoystickDirection>(result);
}

int check_top_right_quadrant(int x, int y)
{
    if(y > JOYSTICK_ACTIVATION_THRESHOLD && x < y * JOYSTICK_ANGLE_CONST)
    {
        // UP
        return 0;
    }
    else if(x > JOYSTICK_ACTIVATION_THRESHOLD && y < x * JOYSTICK_ANGLE_CONST)
    {
        // RIGHT
        return 2;
    }
    else if(x*x + y*y > JOYSTICK_ACTIVATION_THRESHOLD_SQUARED)
    {
        // UP RIGHT
        return 1;
    }
    return -1;
}

std::string get_pin_name(int pin)
{
    switch(pin)
    {
        case X_BUTTON_PIN:
            return "X";
        case Y_BUTTON_PIN:
            return "Y";
        case A_BUTTON_PIN:
            return "A";
        case B_BUTTON_PIN:
            return "B";
        case START_BUTTON_PIN:
            return "START";
        case SELECT_BUTTON_PIN:
            return "SELECT";
        case PLAYER_1_BUTTON_PIN:
            return "PLAYER 1";
        case PLAYER_2_BUTTON_PIN:
            return "PLAYER 2";
        default:
            return "Unknown";
    }
}

std::string print_direction(JoystickDirection direction)
{
    switch(direction)
    {
        case UP:
            return "UP";
        case UP_RIGHT:
            return "UP_RIGHT";
        case RIGHT:
            return "RIGHT";
        case DOWN_RIGHT:
            return "DOWN_RIGHT";
        case DOWN:
            return "DOWN";
        case DOWN_LEFT:
            return "DOWN_LEFT";
        case LEFT:
            return "LEFT";
        case UP_LEFT:
            return "UP_LEFT";
        default:
            return "None";
    }
}