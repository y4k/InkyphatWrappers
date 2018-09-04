#ifndef LIBINKYPHAT_H
#define LIBINKYPHAT_H

#include "inkyphat.h"
#include "constants.h"

extern "C"
{
    int init();
    int set_pixels(unit8_t bytes[]);
    int update();
    int shutdown();
}

#endif