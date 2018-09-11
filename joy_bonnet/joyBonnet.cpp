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