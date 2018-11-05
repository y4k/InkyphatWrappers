#include "interruptBase.hpp"

std::mutex InterruptBase::_lock;

std::map<int, std::set<InterruptBase *>> InterruptBase::_isrTable;

InterruptBase::InterruptBase() {}

bool InterruptBase::Register(int pin, int edge, InterruptBase *interruptTarget)
{
    if (pin < 0 || pin > MAX_PINS)
    {
        return false;
    }
    std::lock_guard<std::mutex> lock(_lock);
    switch (edge)
    {
    case INT_EDGE_FALLING:
        internal_register_falling(pin);
        break;
    case INT_EDGE_RISING:
        internal_register_rising(pin);
        break;
    case INT_EDGE_BOTH:
        internal_register_falling(pin);
        internal_register_rising(pin);
        break;
    default:
        return false;
    }
    _isrTable[pin].insert(interruptTarget);
    return true;
}

void InterruptBase::InterruptHandler(int pin, int edge)
{
    std::lock_guard<std::mutex> lock(_lock);
    std::set<InterruptBase *> &vec = _isrTable[pin];
    for (auto &ptr : vec)
    {
        ptr->ISR(pin, edge);
    }
}

InterruptBase::~InterruptBase()
{
    Unregister(this);
}

bool InterruptBase::Unregister(InterruptBase *intThisPtr)
{
    std::lock_guard<std::mutex> lock(_lock);
    for (int pin = 0; pin < MAX_PINS; pin++)
    {
        std::set<InterruptBase *> &vec = _isrTable[pin];
        for (auto &ptr : vec)
        {
            if (ptr == intThisPtr)
            {
                vec.erase(ptr);
                break;
            }
        }
    }
}

/*
Trivial switch statement that registers the correct static handler for
the correct pin with wiringPi for falling edge interrupts.
*/
void InterruptBase::internal_register_falling(int pin)
{
    switch (pin)
    {
    case 0:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin0);
    case 1:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin1);
    case 2:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin2);
    case 3:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin3);
    case 4:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin4);
    case 5:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin5);
    case 6:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin6);
    case 7:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin7);
    case 8:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin8);
    case 9:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin9);
    case 10:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin10);
    case 11:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin11);
    case 12:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin12);
    case 13:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin13);
    case 14:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin14);
    case 15:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin15);
    case 16:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin16);
    case 17:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin17);
    case 18:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin18);
    case 19:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin19);
    case 20:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin20);
    case 21:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin21);
    case 22:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin22);
    case 23:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin23);
    case 24:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin24);
    case 25:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin25);
    case 26:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin26);
    case 27:
        wiringPiISR(pin, INT_EDGE_RISING, &falling_callback_bcm_pin27);
    }
}

/*
Trivial switch statement that registers the correct static handler for
the correct pin with wiringPi for rising edge interrupts.
*/
void InterruptBase::internal_register_rising(int pin)
{
    switch (pin)
    {
    case 0:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin0);
    case 1:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin1);
    case 2:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin2);
    case 3:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin3);
    case 4:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin4);
    case 5:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin5);
    case 6:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin6);
    case 7:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin7);
    case 8:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin8);
    case 9:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin9);
    case 10:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin10);
    case 11:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin11);
    case 12:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin12);
    case 13:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin13);
    case 14:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin14);
    case 15:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin15);
    case 16:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin16);
    case 17:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin17);
    case 18:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin18);
    case 19:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin19);
    case 20:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin20);
    case 21:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin21);
    case 22:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin22);
    case 23:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin23);
    case 24:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin24);
    case 25:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin25);
    case 26:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin26);
    case 27:
        wiringPiISR(pin, INT_EDGE_RISING, &rising_callback_bcm_pin27);
    }
}

void InterruptBase::rising_callback_bcm_pin0()
{
    InterruptHandler(0, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin0()
{
    InterruptHandler(0, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin1()
{
    InterruptHandler(1, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin1()
{
    InterruptHandler(1, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin2()
{
    InterruptHandler(2, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin2()
{
    InterruptHandler(2, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin3()
{
    InterruptHandler(3, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin3()
{
    InterruptHandler(3, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin4()
{
    InterruptHandler(4, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin4()
{
    InterruptHandler(4, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin5()
{
    InterruptHandler(5, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin5()
{
    InterruptHandler(5, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin6()
{
    InterruptHandler(6, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin6()
{
    InterruptHandler(6, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin7()
{
    InterruptHandler(7, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin7()
{
    InterruptHandler(7, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin8()
{
    InterruptHandler(8, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin8()
{
    InterruptHandler(8, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin9()
{
    InterruptHandler(9, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin9()
{
    InterruptHandler(9, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin10()
{
    InterruptHandler(10, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin10()
{
    InterruptHandler(10, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin11()
{
    InterruptHandler(11, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin11()
{
    InterruptHandler(11, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin12()
{
    InterruptHandler(12, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin12()
{
    InterruptHandler(12, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin13()
{
    InterruptHandler(13, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin13()
{
    InterruptHandler(13, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin14()
{
    InterruptHandler(14, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin14()
{
    InterruptHandler(14, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin15()
{
    InterruptHandler(15, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin15()
{
    InterruptHandler(15, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin16()
{
    InterruptHandler(16, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin16()
{
    InterruptHandler(16, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin17()
{
    InterruptHandler(17, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin17()
{
    InterruptHandler(17, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin18()
{
    InterruptHandler(18, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin18()
{
    InterruptHandler(18, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin19()
{
    InterruptHandler(19, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin19()
{
    InterruptHandler(19, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin20()
{
    InterruptHandler(20, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin20()
{
    InterruptHandler(20, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin21()
{
    InterruptHandler(21, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin21()
{
    InterruptHandler(21, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin22()
{
    InterruptHandler(22, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin22()
{
    InterruptHandler(22, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin23()
{
    InterruptHandler(23, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin23()
{
    InterruptHandler(23, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin24()
{
    InterruptHandler(24, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin24()
{
    InterruptHandler(24, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin25()
{
    InterruptHandler(25, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin25()
{
    InterruptHandler(25, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin26()
{
    InterruptHandler(26, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin26()
{
    InterruptHandler(26, INT_EDGE_FALLING);
}
void InterruptBase::rising_callback_bcm_pin27()
{
    InterruptHandler(27, INT_EDGE_RISING);
}
void InterruptBase::falling_callback_bcm_pin27()
{
    InterruptHandler(27, INT_EDGE_FALLING);
}
