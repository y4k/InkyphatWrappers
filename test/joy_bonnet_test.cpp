#include "joyBonnetConstants.h"
#include "joyBonnet.h"

using namespace std;

int main(void)
{
    // sets up the wiringPi library
    if (wiringPiSetupGpio() < 0)
    {
        fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
        return 1;
    }

    JoyBonnet &joy = JoyBonnet::Instance();

    joy.addHandler(X_BUTTON_PIN, {[]()
    {
        cout << "X Button!" << endl;
        return;
    }});

    // display counter value every second.
    while (1)
    {
        int x = joy.read_joystick_x();
        int y = joy.read_joystick_y();
        cout << "(X,Y) -> [" << x << "," << y << "]" << endl;

        int xCoord, yCoord;
        tie(xCoord, yCoord) = joy.read_joystick_coords();

        cout << "Tuple -> [" << xCoord << "," << yCoord << "]" << endl;

        cout << print_direction(joy.read_joystick_direction()) << endl;
        delay(100); // wait 1 second
    }
    
    return 0;
}
