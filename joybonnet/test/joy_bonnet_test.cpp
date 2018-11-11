#include "joyBonnet.hpp"
#include "joyBonnetConstants.hpp"

int main(void)
{
  // sets up the wiringPi library
  if (wiringPiSetupGpio() < 0)
  {
    std::cout << "Unable to setup wiringPi:" << strerror(errno) << std::endl;
    return -1;
  }

  JoyBonnet &joy = JoyBonnet::Instance();

  volatile int x_count = 0;

  joy.addHandler(X_BUTTON_PIN, {[&x_count]() {
                   x_count++;
                   std::cout << x_count << ":X Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(Y_BUTTON_PIN, {[=]() {
                   std::cout << "Y Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(A_BUTTON_PIN, {[=]() {
                   std::cout << "A Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(B_BUTTON_PIN, {[=]() {
                   std::cout << "B Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(START_BUTTON_PIN, {[=]() {
                   std::cout << "Start Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(SELECT_BUTTON_PIN, {[=]() {
                   std::cout << "Select Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(PLAYER_1_BUTTON_PIN, {[=]() {
                   std::cout << "Player 1 Button!" << std::endl;
                   return;
                 }});
  joy.addHandler(PLAYER_2_BUTTON_PIN, {[=]() {
                   std::cout << "Player 2 Button!" << std::endl;
                   return;
                 }});

  std::cout << "Main thread:" << this_thread::get_id() << std::endl;

  while (1)
  {
    // int xCoord, yCoord;
    // tie(xCoord, yCoord) = joy.read_joystick_coords();

    // std::cout << "Tuple -> [" << xCoord << "," << yCoord << "]" << std::endl;

    std::cout << print_direction(joy.read_joystick_direction()) << std::endl;
    delay(100); // wait 100 millisecond
  }

  return 0;
}
