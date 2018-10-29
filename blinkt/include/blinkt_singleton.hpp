#include "blinkt.hpp"

class BlinktSingleton
{
  public:
    static Blinkt &Instance()
    {
        static BlinktSingleton instance;
        return instance.get_blinkt();
    }
    BlinktSingleton(BlinktSingleton const &) = delete;
    void operator=(BlinktSingleton const &) = delete;
    ~BlinktSingleton();

  private:
    BlinktSingleton();
    Blinkt &get_blinkt();
};