#ifndef INTERRUPT_BASE_H
#define INTERRUPT_BASE_H

#include <wiringPi.h>
#include <wiringPiI2C.h>

class InterruptBase
{
public:
  InterruptBase();
  virtual void ISR(int pin, int edge) = 0;
  static void RaiseInterrupt(int interrupt)
  {
    switch (interrupt)
    {
    case 0:
      Interrupt0(1);
      break;
    case 1:
      Interrupt1(1);
      break;
    case 2:
      Interrupt2(1);
      break;
    }
  }

protected:
  static bool Register(int interrupt, InterruptBase *intThisPtr)
  {
    return _isrTable[interrupt].insert(intThisPtr).second;
  }

private:
  static std::map<int, std::set<InterruptBase *>> _isrTable;
  static void Interrupt0(int edge) { InterruptHandler(0, edge); }
  static void Interrupt1(int edge) { InterruptHandler(1, edge); }
  static void Interrupt2(int edge) { InterruptHandler(2, edge); }
  static void InterruptHandler(int pin, int edge)
  {
    std::set<InterruptBase *> &vec = _isrTable[pin];
    for (auto &ptr : vec)
    {
      ptr->ISR(pin, edge);
    }
  }

  static void _rising_callback_bcm_pin0();
  static void _falling_callback_bcm_pin0();
  static void _rising_callback_bcm_pin1();
  static void _falling_callback_bcm_pin1();
  static void _rising_callback_bcm_pin2();
  static void _falling_callback_bcm_pin2();
  static void _rising_callback_bcm_pin3();
  static void _falling_callback_bcm_pin3();
  static void _rising_callback_bcm_pin4();
  static void _falling_callback_bcm_pin4();
  static void _rising_callback_bcm_pin5();
  static void _falling_callback_bcm_pin5();
  static void _rising_callback_bcm_pin6();
  static void _falling_callback_bcm_pin6();
  static void _rising_callback_bcm_pin7();
  static void _falling_callback_bcm_pin7();
  static void _rising_callback_bcm_pin8();
  static void _falling_callback_bcm_pin8();
  static void _rising_callback_bcm_pin9();
  static void _falling_callback_bcm_pin9();
  static void _rising_callback_bcm_pin10();
  static void _falling_callback_bcm_pin10();
  static void _rising_callback_bcm_pin11();
  static void _falling_callback_bcm_pin11();
  static void _rising_callback_bcm_pin12();
  static void _falling_callback_bcm_pin12();
  static void _rising_callback_bcm_pin13();
  static void _falling_callback_bcm_pin13();
  static void _rising_callback_bcm_pin14();
  static void _falling_callback_bcm_pin14();
  static void _rising_callback_bcm_pin15();
  static void _falling_callback_bcm_pin15();
  static void _rising_callback_bcm_pin16();
  static void _falling_callback_bcm_pin16();
  static void _rising_callback_bcm_pin17();
  static void _falling_callback_bcm_pin17();
  static void _rising_callback_bcm_pin18();
  static void _falling_callback_bcm_pin18();
  static void _rising_callback_bcm_pin19();
  static void _falling_callback_bcm_pin19();
  static void _rising_callback_bcm_pin20();
  static void _falling_callback_bcm_pin20();
  static void _rising_callback_bcm_pin21();
  static void _falling_callback_bcm_pin21();
  static void _rising_callback_bcm_pin22();
  static void _falling_callback_bcm_pin22();
  static void _rising_callback_bcm_pin23();
  static void _falling_callback_bcm_pin23();
  static void _rising_callback_bcm_pin24();
  static void _falling_callback_bcm_pin24();
  static void _rising_callback_bcm_pin25();
  static void _falling_callback_bcm_pin25();
  static void _rising_callback_bcm_pin26();
  static void _falling_callback_bcm_pin26();
  static void _rising_callback_bcm_pin27();
  static void _falling_callback_bcm_pin27();
};

#endif