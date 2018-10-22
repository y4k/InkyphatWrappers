#ifndef INTERRUPT_BASE_H
#define INTERRUPT_BASE_H

#include <map>
#include <set>
#include <mutex>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define MAX_PINS 27

class InterruptBase
{
public:
protected:
  virtual void ISR(int pin, int edge) = 0;
  InterruptBase();
  static bool Register(int pin, int edge, InterruptBase *interruptTarget);
  static bool Unregister(InterruptBase *intThisPtr);
  virtual ~InterruptBase();

private:
  static std::mutex _lock;
  static std::map<int, std::set<InterruptBase *>> _isrTable;
  static void InterruptHandler(int pin, int edge);

  static void internal_register_falling(int pin);
  static void internal_register_rising(int pin);

  static void rising_callback_bcm_pin0();
  static void falling_callback_bcm_pin0();
  static void rising_callback_bcm_pin1();
  static void falling_callback_bcm_pin1();
  static void rising_callback_bcm_pin2();
  static void falling_callback_bcm_pin2();
  static void rising_callback_bcm_pin3();
  static void falling_callback_bcm_pin3();
  static void rising_callback_bcm_pin4();
  static void falling_callback_bcm_pin4();
  static void rising_callback_bcm_pin5();
  static void falling_callback_bcm_pin5();
  static void rising_callback_bcm_pin6();
  static void falling_callback_bcm_pin6();
  static void rising_callback_bcm_pin7();
  static void falling_callback_bcm_pin7();
  static void rising_callback_bcm_pin8();
  static void falling_callback_bcm_pin8();
  static void rising_callback_bcm_pin9();
  static void falling_callback_bcm_pin9();
  static void rising_callback_bcm_pin10();
  static void falling_callback_bcm_pin10();
  static void rising_callback_bcm_pin11();
  static void falling_callback_bcm_pin11();
  static void rising_callback_bcm_pin12();
  static void falling_callback_bcm_pin12();
  static void rising_callback_bcm_pin13();
  static void falling_callback_bcm_pin13();
  static void rising_callback_bcm_pin14();
  static void falling_callback_bcm_pin14();
  static void rising_callback_bcm_pin15();
  static void falling_callback_bcm_pin15();
  static void rising_callback_bcm_pin16();
  static void falling_callback_bcm_pin16();
  static void rising_callback_bcm_pin17();
  static void falling_callback_bcm_pin17();
  static void rising_callback_bcm_pin18();
  static void falling_callback_bcm_pin18();
  static void rising_callback_bcm_pin19();
  static void falling_callback_bcm_pin19();
  static void rising_callback_bcm_pin20();
  static void falling_callback_bcm_pin20();
  static void rising_callback_bcm_pin21();
  static void falling_callback_bcm_pin21();
  static void rising_callback_bcm_pin22();
  static void falling_callback_bcm_pin22();
  static void rising_callback_bcm_pin23();
  static void falling_callback_bcm_pin23();
  static void rising_callback_bcm_pin24();
  static void falling_callback_bcm_pin24();
  static void rising_callback_bcm_pin25();
  static void falling_callback_bcm_pin25();
  static void rising_callback_bcm_pin26();
  static void falling_callback_bcm_pin26();
  static void rising_callback_bcm_pin27();
  static void falling_callback_bcm_pin27();
};

#endif