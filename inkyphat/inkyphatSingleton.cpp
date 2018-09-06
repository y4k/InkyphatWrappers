#include <iostream>
#include <stdint.h>
#include <string>
#include <linux/types.h>
#include <signal.h> // some kind of magic I guess
#include <iostream>
#include <unistd.h>  // usleep
#include <stdlib.h>
#include <mutex>

#include "inkyphat.h"

using namespace std;

class InkyphatSingleton
{
    public:
      static InkyphatSingleton& Instance()
      {
          static InkyphatSingleton instance;
          return instance;
      }
      InkyphatSingleton(InkyphatSingleton const &) = delete;
      void operator=(InkyphatSingleton const &) = delete;
    private:
      InkyphatSingleton(){};
};