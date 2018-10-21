#include "interruptBase.hpp"

std::map<int, std::set<InterruptBase *>> InterruptBase::_isrTable;

IsrHelper::IsrHelper {}

void IsrHelper::register_callback(int edge, int pin,
                                  std::function<void(void)> cb) {
  wiringPiISR(pin, edge, &x_callback_rising);
  switch (pin) {
      case 0;
  }
}

void IsrHelper::execute_callback(int edge, int pin)
{

}

void IsrHelper::_rising_callback_bcm_pin0()
{
    IsrHelper& instance = IsrHelper::Instance();
}