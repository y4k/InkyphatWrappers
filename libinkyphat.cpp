#include <stdint.h>
#include <string>
#include <linux/types.h>
#include <unistd.h>  // usleep
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Local headers
#include "libinkyphat.h"

InkyPhat *display;
bool initialised = false;

extern "C"
{
    int init()
    {
        if(initialised)
        {
            #ifdef DEBUG
                cout << "init() called when already initialised" << endl;
            #endif
            return 3;
        }

        // Initialises wiringPi and uses the wiringPi pin numbering scheme
        if(wiringPiSetupGpio() == -1)
        {
            #ifdef DEBUG
                cout << "Failed to initialise WiringPi" << endl;
            #endif

            return 1;
        }
        #ifdef DEBUG
            cout << "WiringPi correctly initialised" << endl;
        #endif

        if(wiringPiSPISetup(CS0_PIN, 488000) == -1)
        {
            #ifdef DEBUG
                cout << "Could not initialise WiringPi SPI library" << endl;
            #endif

            return 2;
        }
        #ifdef DEBUG
            cout << "WiringPi SPI library initialised" << endl;
        #endif

        display = new InkyPhat();

        initialised = true;

        return 0;
    }

    const int valuesSize = 22048; // 104 * 212;

    int set_pixels(array<unit8_t> values)
    {
        if(!initialised)
        {
            #ifdef DEBUG
                cout << "InkyPhat set_pixels called when uninitialised" << endl;
            #endif
            return 1;
        }

        // The data is expected as a single array that is 104x212 long
        int length = sizeof(values) / sizeof(values[0]);
        if (length != valuesSize)
        {
            #ifdef DEBUG
                cout << "Values array passed to set_pixel() was not the correct length:" << length << endl;
            #endif
            return 2;
        }

        //All values must be either 0, 1 or 2
        for(int i = 0; i < valuesSize; i++)
        {
            if(values[i] < 0 || values[i] > 2)
            {
                #ifdef DEBUG
                    cout << "Values array contained a value at index [" << i << "] that was {" << unsigned(values[i])
                    << "} which is not 0, 1 or 2" << endl;
                #endif
                return 3;
            }
        }
        
        // Partition the array into chunks of 104.
        for(int col_index = 0; col_index < valuesSize; col_index += 104)
        {
            for(int row_index = col_index; row_index < col_index + 104; row_index++)
            {
                if(inky.set_pixel(row_index, col_index, values[col_index+row_index]) == -1)
                {
                    #ifdef DEBUG
                        cout << "Failed to set pixel at [" << col_index << "][" << row_index << "] with value {" << unsigned(values[col_index+row_index])
                        << "}" << endl;
                    #endif
                    return 4;
                }
            }
        }

        return 0;
    }

    int update()
    {
        if(!initialised)
        {
            #ifdef DEBUG
                cout << "InkyPhat update called when uninitialised" << endl;
            #endif
            return 1;
        }
        #ifdef DEBUG
            cout << "InkyPhat updating" << endl;
        #endif
        return display -> update();
    }

    int shutdown()
    {
        if(!initialised)
        {
            #ifdef DEBUG
                cout << "InkyPhat library shutdown called when unitialised. Call init() to initialise." << endl;
            #endif
            return 1;
        }
        #ifdef DEBUG
            cout << "InkyPhat library shutdown. Call init() to re-initialise." << endl;
        #endif

        initialised = false;
        delete display;
        return 0;
    }
}