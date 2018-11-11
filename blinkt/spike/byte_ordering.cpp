#include <iostream>

void print_lsb(uint8_t byte)
{
    std::cout << "LSB:" << std::endl;
    for (int n = 0; n < 8; n++)
    {
        uint8_t b = ((byte >> n) & 0b1);
        std::cout << unsigned(b);
    }
    std::cout << std::endl;
}

void print_msb(uint8_t byte)
{
    std::cout << "MSB:" << std::endl;
    for (int n = 0; n < 8; n++)
    {
        uint8_t b = (byte & (1 << (7 - n))) >> (7 - n);
        std::cout << unsigned(b);
    }
    std::cout << std::endl;
}

int main(void)
{
    uint8_t value = 0b11111;
    print_lsb(value);
    print_msb(value);
    return 0;
}