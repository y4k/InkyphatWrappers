#include "joyBonnet.h"

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
    if (wiringPiI2CSetup(ADS1x15_DEFAULT_ADDRESS) == -1)
    {
        cout << "Wiring Pi i2c setup failed:" << std::strerror(errno) << endl;
    }
}

void JoyBonnet::x_callback(void)
{
    cout << "Executing for X" << endl;
    JoyBonnet::Instance().execute_callbacks(X_BUTTON_PIN);
}

void JoyBonnet::y_callback(void)
{
    cout << "Executing for Y" << endl;
    JoyBonnet::Instance().execute_callbacks(Y_BUTTON_PIN);
}

void JoyBonnet::a_callback(void)
{
    cout << "Executing for A" << endl;
    JoyBonnet::Instance().execute_callbacks(A_BUTTON_PIN);
}

void JoyBonnet::b_callback(void)
{
    cout << "Executing for B" << endl;
    JoyBonnet::Instance().execute_callbacks(B_BUTTON_PIN);
}

void JoyBonnet::start_callback(void)
{
    cout << "Executing for START" << endl;
    JoyBonnet::Instance().execute_callbacks(START_BUTTON_PIN);
}

void JoyBonnet::select_callback(void)
{
    cout << "Executing for SELECT" << endl;
    JoyBonnet::Instance().execute_callbacks(SELECT_BUTTON_PIN);
}

void JoyBonnet::p1_callback(void)
{
    cout << "Executing for PLAYER 1" << endl;
    JoyBonnet::Instance().execute_callbacks(PLAYER_1_BUTTON_PIN);
}

void JoyBonnet::p2_callback(void)
{
    cout << "Executing for PLAYER 2" << endl;
    JoyBonnet::Instance().execute_callbacks(PLAYER_2_BUTTON_PIN);
}

void JoyBonnet::execute_callbacks(int pin)
{
    auto cb = _callbacks[pin];
    for_each(cb.begin(), cb.end(), [](function<void()> f) { f(); });
}

void JoyBonnet::addHandler(int pin, const function<void()> callback)
{
    cout << "Handler added for " << pin << endl;
    _callbacks[pin].push_back(callback);
}

void JoyBonnet::read_joystick(int channel)
{
    configword = ADS1015_REG_CONFIG_CQUE_NONE |
                 ADS1015_REG_CONFIG_CLAT_NONLAT |
                 ADS1015_REG_CONFIG_CPOL_ACTVLOW |
                 ADS1015_REG_CONFIG_CMODE_TRAD |
                 ADS1015_REG_CONFIG_DR_1600SPS |
                 ADS1015_REG_CONFIG_MODE_SINGLE |
                 ADS1015_REG_CONFIG_GAIN_ONE |
                 _channels[channel] |
                 ADS1015_REG_CONFIG_OS_SINGLE;

    configdata = [configword >> 8, configword & 0xFF]

    //print("Setting config byte = 0x%02X%02X" % (configdata[0], configdata[1]))
    bus.write_i2c_block_data(ADS1x15_DEFAULT_ADDRESS, ADS1x15_POINTER_CONFIG, configdata)

    configdata = bus.read_i2c_block_data(ADS1x15_DEFAULT_ADDRESS, ADS1x15_POINTER_CONFIG, 2) 
    //print("Getting config byte = 0x%02X%02X" % (configdata[0], configdata[1]))

    while True:
        try:
        configdata = bus.read_i2c_block_data(ADS1x15_DEFAULT_ADDRESS, ADS1x15_POINTER_CONFIG, 2) 
        //print("Getting config byte = 0x%02X%02X" % (configdata[0], configdata[1]))
        if (configdata[0] & 0x80):
            break
        except:
        pass
    
    
    //read data out!
    analogdata = bus.read_i2c_block_data(ADS1x15_DEFAULT_ADDRESS, ADS1x15_POINTER_CONVERSION, 2)
    //print(analogdata),
    retval = (analogdata[0] << 8) | analogdata[1]
    retval /= 16
    //print("-> %d" %retval)
    return retval
}