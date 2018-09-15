#include "joyBonnet.h"

using namespace std;

JoyBonnet::JoyBonnet()
{
    pullUpDnControl(X_BUTTON_PIN, PUD_UP);
    wiringPiISR(X_BUTTON_PIN, INT_EDGE_RISING, &x_callback);
    
    pullUpDnControl(Y_BUTTON_PIN, PUD_UP);
    wiringPiISR(Y_BUTTON_PIN, INT_EDGE_RISING, &y_callback);
    
    pullUpDnControl(A_BUTTON_PIN, PUD_UP);
    wiringPiISR(A_BUTTON_PIN, INT_EDGE_RISING, &a_callback);
    
    pullUpDnControl(B_BUTTON_PIN, PUD_UP);
    wiringPiISR(B_BUTTON_PIN, INT_EDGE_RISING, &b_callback);

    pullUpDnControl(START_BUTTON_PIN, PUD_UP);
    wiringPiISR(START_BUTTON_PIN, INT_EDGE_RISING, &start_callback);

    pullUpDnControl(SELECT_BUTTON_PIN, PUD_UP);
    wiringPiISR(SELECT_BUTTON_PIN, INT_EDGE_RISING, &select_callback);
    
    pullUpDnControl(PLAYER_1_BUTTON_PIN, PUD_UP);
    wiringPiISR(PLAYER_1_BUTTON_PIN, INT_EDGE_RISING, &p1_callback);
    
    pullUpDnControl(PLAYER_2_BUTTON_PIN, PUD_UP);
    wiringPiISR(PLAYER_2_BUTTON_PIN, INT_EDGE_RISING, &p2_callback);

    // Setup i2c communication to the joystick
    if ( (_i2cFileHandler = wiringPiI2CSetup(ADS1x15_DEFAULT_ADDRESS)) == -1)
    {
        cout << "Wiring Pi i2c setup failed:" << strerror(errno) << endl;
    }
}

void JoyBonnet::x_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(X_BUTTON_PIN);
}

void JoyBonnet::y_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(Y_BUTTON_PIN);
}

void JoyBonnet::a_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(A_BUTTON_PIN);
}

void JoyBonnet::b_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(B_BUTTON_PIN);
}

void JoyBonnet::start_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(START_BUTTON_PIN);
}

void JoyBonnet::select_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(SELECT_BUTTON_PIN);
}

void JoyBonnet::p1_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(PLAYER_1_BUTTON_PIN);
}

void JoyBonnet::p2_callback(void)
{
    JoyBonnet::Instance().execute_callbacks(PLAYER_2_BUTTON_PIN);
}

void JoyBonnet::execute_callbacks(int pin)
{
    auto cb = _callbacks[pin];
    for_each(cb.begin(), cb.end(), [](function<void()> f) { f(); });
}

void JoyBonnet::addHandler(int pin, const function<void()> callback)
{
    _callbacks[pin].push_back(callback);
}

int JoyBonnet::read_joystick(int channel)
{
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
        cout << "Wiring Pi Write16 Reg failed:" << strerror(errno) << endl;
    }

    int readValue = wiringPiI2CReadReg16(_i2cFileHandler, ADS1x15_POINTER_CONFIG);

    while (1)
    {
        readValue = wiringPiI2CReadReg16(_i2cFileHandler, ADS1x15_POINTER_CONFIG);

        if (((readValue >> 8) & 0xFF) & 0x80)
        {
            int analogdata = wiringPiI2CReadReg16(_i2cFileHandler, ADS1x15_POINTER_CONVERSION);

            int b1 = (analogdata >> 8);
            int b2 = (analogdata & 0xFF);
            // cout << b1 << endl;
            // cout << b2 << endl;

            cout << ((b1 << 8)|b2) << endl;
            cout << ((b2 << 8)|b1) << endl; // It's this ONE!!!!

            int value = (analogdata >> 4) & 0xFFF; // Gets 12 bit value and mask it just in case
            // cout << "Channel[" << channel << "]: " << value << endl;
            return analogdata/16;
        }
    }
}

int JoyBonnet::read_joystick_x()
{
    return read_joystick(1);
}

int JoyBonnet::read_joystick_y()
{
    return -read_joystick(0);
}