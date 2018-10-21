#include "interruptBase.hpp"

std::map<int, std::set<InterruptBase *>> InterruptBase::_isrTable;

InterruptBase::InterruptBase() {}

static bool InterruptBase::Register(int pin, int edge, InterruptBase *interruptTarget);
{
    switch (edge)
    {
    case INT_EDGE_FALLING:
        internal_register_falling(int pin);
        break;
    case INT_EDGE_RISING:
        internal_register_rising(int pin);
        break;
    case INT_EDGE_BOTH:
        internal_register_falling(int pin);
        internal_register_rising(int pin);
        break;
    default:
        return false;
    }
    std::lock_guard<std::mutex> lock(_lock);
    return _isrTable[pin].insert(interruptTarget).second;
}

static void InterruptBase::InterruptHandler(int pin, int edge)
{
    std::lock_guard<std::mutex> lock(_lock);
    std::set<InterruptBase *> &vec = _isrTable[pin];
    for (auto &ptr : vec)
    {
        ptr->ISR(pin, edge);
    }
}

/*
Trivial switch statement that registers the correct static handler for
the correct pin with wiringPi for falling edge interrupts.
*/
static void InterruptBase::internal_register_rising(int pin)
{
    switch (pin)
    {
    case 0:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin0);
    case 1:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin1);
    case 2:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin2);
    case 3:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin3);
    case 4:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin4);
    case 5:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin5);
    case 6:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin6);
    case 7:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin7);
    case 8:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin8);
    case 9:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin9);
    case 10:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin10);
    case 11:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin11);
    case 12:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin12);
    case 13:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin13);
    case 14:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin14);
    case 15:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin15);
    case 16:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin16);
    case 17:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin17);
    case 18:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin18);
    case 19:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin19);
    case 20:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin20);
    case 21:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin21);
    case 22:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin22);
    case 23:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin23);
    case 24:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin24);
    case 25:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin25);
    case 26:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin26);
    case 27:
        wiringPiIsr(pin, INT_EDGE_RISING, &falling_callback_bcm_pin27);
    }
}

/*
Trivial switch statement that registers the correct static handler for
the correct pin with wiringPi for rising edge interrupts.
*/
static void InterruptBase::internal_register_rising(int pin)
{
    switch (pin)
    {
    case 0:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin0);
    case 1:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin1);
    case 2:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin2);
    case 3:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin3);
    case 4:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin4);
    case 5:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin5);
    case 6:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin6);
    case 7:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin7);
    case 8:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin8);
    case 9:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin9);
    case 10:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin10);
    case 11:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin11);
    case 12:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin12);
    case 13:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin13);
    case 14:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin14);
    case 15:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin15);
    case 16:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin16);
    case 17:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin17);
    case 18:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin18);
    case 19:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin19);
    case 20:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin20);
    case 21:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin21);
    case 22:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin22);
    case 23:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin23);
    case 24:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin24);
    case 25:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin25);
    case 26:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin26);
    case 27:
        wiringPiIsr(pin, INT_EDGE_RISING, &rising_callback_bcm_pin27);
    }
}

void InterruptBase::rising_callback_bcm_pin0()
{
    InterruptHandler(0, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin0()
{
    InterruptHandler(0, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin1()
{
    InterruptHandler(1, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin1()
{
    InterruptHandler(1, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin2()
{
    InterruptHandler(2, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin2()
{
    InterruptHandler(2, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin3()
{
    InterruptHandler(3, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin3()
{
    InterruptHandler(3, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin4()
{
    InterruptHandler(4, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin4()
{
    InterruptHandler(4, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin5()
{
    InterruptHandler(5, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin5()
{
    InterruptHandler(5, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin6()
{
    InterruptHandler(6, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin6()
{
    InterruptHandler(6, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin7()
{
    InterruptHandler(7, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin7()
{
    InterruptHandler(7, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin8()
{
    InterruptHandler(8, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin8()
{
    InterruptHandler(8, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin9()
{
    InterruptHandler(9, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin9()
{
    InterruptHandler(9, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin10()
{
    InterruptHandler(10, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin10()
{
    InterruptHandler(10, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin11()
{
    InterruptHandler(11, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin11()
{
    InterruptHandler(11, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin12()
{
    InterruptHandler(12, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin12()
{
    InterruptHandler(12, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin13()
{
    InterruptHandler(13, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin13()
{
    InterruptHandler(13, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin14()
{
    InterruptHandler(14, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin14()
{
    InterruptHandler(14, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin15()
{
    InterruptHandler(15, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin15()
{
    InterruptHandler(15, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin16()
{
    InterruptHandler(16, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin16()
{
    InterruptHandler(16, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin17()
{
    InterruptHandler(17, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin17()
{
    InterruptHandler(17, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin18()
{
    InterruptHandler(18, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin18()
{
    InterruptHandler(18, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin19()
{
    InterruptHandler(19, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin19()
{
    InterruptHandler(19, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin20()
{
    InterruptHandler(20, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin20()
{
    InterruptHandler(20, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin21()
{
    InterruptHandler(21, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin21()
{
    InterruptHandler(21, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin22()
{
    InterruptHandler(22, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin22()
{
    InterruptHandler(22, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin23()
{
    InterruptHandler(23, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin23()
{
    InterruptHandler(23, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin24()
{
    InterruptHandler(24, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin24()
{
    InterruptHandler(24, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin25()
{
    InterruptHandler(25, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin25()
{
    InterruptHandler(25, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin26()
{
    InterruptHandler(26, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin26()
{
    InterruptHandler(26, INT_FALLING_EDGE);
}
void InterruptBase::rising_callback_bcm_pin27()
{
    InterruptHandler(27, INT_RISING_EDGE);
}
void InterruptBase::falling_callback_bcm_pin27()
{
    InterruptHandler(27, INT_FALLING_EDGE);
}