#include "skywriter.hpp"

Header parse_header(char[] bytes)
{
    struct Header h = {.MessageSize = char[0], .Sequence = char[2], .ID = char[3]};
    return h;
}

Skywriter::Skywriter()
{
    // Set the reset pin to an output and give it the initial value of HIGH
    pinMode(SW_RESET_PIN, OUTPUT);
    digitalWrite(SW_RESET_PIN, HIGH);

    // Set the Transfer pin to an input and configure a pull up resistor
    pinMode(SW_TRFR_PIN, INPUT);
    pullUpDnControl(SW_TRFR_PIN, PUD_UP);
    wiringPiISR(SW_TRFR_PIN, INT_EDGE_RISING, &trfr_callback_rising);
    wiringPiISR(SW_TRFR_PIN, INT_EDGE_FALLING, &trfr_callback_falling);

    // Setup i2c communication to the Skywriter
    if ( (_i2cFileHandler = wiringPiI2CSetup(SW_ADDR_1)) == -1)
    {
        #ifdef DEBUG
        std::cout << "Wiring Pi i2c setup failed:" << strerror(errno) << std::endl;
        #endif
    }
}

Skywriter::~Skywriter()
{

}

void Skywriter::trfr_callback_falling()
{
    #if DEBUG
    std::cout << "Line pulled low by chip" << std::endl;
    #endif

    Skywriter &instance = Skywriter::Instance();
}

void Skywriter::trfr_callback_rising()
{
    Skywriter &instance = Skywriter::Instance();
}

void Skywriter::start_transfer()
{
    #if DEBUG
    std::cout << "TRFR line is asserted low by the host" << std::endl;
    #endif
    
    pinMode(SW_TRFR_PIN, OUTPUT);
    digitalWrite(SW_TRFR_PIN, LOW);
}

void Skywriter::complete_transfer()
{
    #if DEBUG
    std::cout << "TRFR line is released by the host" << std::endl;
    #endif

    // Set the Transfer pin to an input and configure a pull up resistor
    pinMode(SW_TRFR_PIN, INPUT);
    pullUpDnControl(SW_TRFR_PIN, PUD_UP);
}
