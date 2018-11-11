#include <iostream>
#include <linux/types.h>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <unistd.h> // usleep

#include "inkyphat.hpp"
#include "inkyphatConstants.hpp"

// VERSION 2 only
InkyPhat::InkyPhat(asio::io_context &io)
    : mIo{io}, mCommandPin{COMMAND_PIN}, mResetPin{RESET_PIN},
      mBusyPin{BUSY_PIN}, mCsPin{CS0_PIN}, mInkyVersion{2},
      mWidth{WIDTH},
      mHeight{HEIGHT},
      mBuffer(mWidth, std::vector<uint8_t>(mHeight))
{
  /*
     Initialise by filling the pixel buffer.
     Indexed using mBuffer[mHeight][mWidth] e.g mBuffer[y][x] or mBuffer[row][column]

    The number of columns (212) represents the long side of the InkyPhat which we
    define as the width with the short side (104) as the height.
    */
  // ========================================

#ifdef DEBUG
  std::cout << std::endl
            << "Pin Setup" << std::endl;
  //GPIO.setup(mCommandPin, GPIO.OUT, initial=GPIO.LOW, pull_up_down=GPIO.PUD_OFF)
  std::cout << "   -> CommandPin:" << unsigned(mCommandPin) << std::endl;
  // Set the COMMAND_PIN as output
  std::cout << "      Mode:" << OUTPUT << std::endl;
#endif
  pinMode(mCommandPin, OUTPUT);
  // Set the pull-up-down resistor to off
  pullUpDnControl(mCommandPin, PUD_OFF);
#ifdef DEBUG
  // Set the state to LOW
  std::cout << "      InitialState:" << LOW << std::endl;
#endif
  digitalWrite(mCommandPin, LOW);

#ifdef DEBUG
  //GPIO.setup(mResetPin, GPIO.OUT, initial=GPIO.HIGH, pull_up_down=GPIO.PUD_OFF)
  std::cout << "   -> ResetPin:" << unsigned(mResetPin) << std::endl;
  // Set the RESET_PIN as output
  std::cout << "      Mode:" << OUTPUT << std::endl;
#endif
  pinMode(mResetPin, OUTPUT);
  // Set the pull-up-down resistor to off
  pullUpDnControl(mResetPin, PUD_OFF);
#ifdef DEBUG
  // Set the state to HIGH
  std::cout << "      InitialState:" << HIGH << std::endl;
#endif
  digitalWrite(mResetPin, HIGH);

#ifdef DEBUG
  //GPIO.setup(mBusyPin, GPIO.IN, pull_up_down=GPIO.PUD_OFF)
  std::cout << "   -> BusyPin:" << unsigned(mBusyPin) << std::endl;
  // Set the BUSY_PIN as input
  std::cout << "      Mode:" << INPUT << std::endl;
#endif
  pinMode(mBusyPin, INPUT);
  // Set the pull-up-down resistor to off
  pullUpDnControl(mResetPin, PUD_OFF);

  //GPIO.output(mResetPin, GPIO.LOW) - Set reset pin to low
  digitalWrite(mResetPin, LOW);
  //sleep for 0.1ms - time.sleep(0.1)
  usleep(100);
  //GPIO.output(mResetPin, GPIO.HIGH) - set reset pin to high
  digitalWrite(mResetPin, HIGH);
  //sleep for 0.1ms - time.sleep(0.1)
  usleep(100);

  if (digitalRead(mBusyPin) == HIGH)
  {
#ifdef DEBUG
    std::cout << "InkyHat version:" << 1 << std::endl;
#endif
    mInkyVersion = 1;
    mPalette.push_back(BLACK);
    mPalette.push_back(WHITE);
    mPalette.push_back(RED);
  }
  else if (digitalRead(mBusyPin) == LOW)
  {
#ifdef DEBUG
    std::cout << "InkyHat version:" << 2 << std::endl;
#endif
    mInkyVersion = 2;
    mPalette.push_back(WHITE);
    mPalette.push_back(BLACK);
    mPalette.push_back(RED);
  }
}

InkyPhat::~InkyPhat()
{
#ifdef DEBUG
  std::cout << "InkyPhat Destructor" << std::endl;
#endif
}

asio::io_context &InkyPhat::get_io_context() const { return mIo; }

int const InkyPhat::operator()(int const x, int const y, uint8_t value)
{
  return set_pixel(y, x, value);
}

int InkyPhat::update()
{
  // Lock to avoid to threads attempting to update at once
  std::lock_guard<std::mutex> lock(mLock);

  display_init();

  std::vector<uint8_t> red_buffer;
  std::vector<uint8_t> black_buffer;

  // Iterate over the long side (212 columns)
  for (std::vector<std::vector<uint8_t>>::iterator col_it = mBuffer.begin(); col_it != mBuffer.end(); col_it++)
  {
    int count = 0;

    // Start with empty value
    uint8_t redValue = 0;
    uint8_t blackValue = 0;

    // Iterate over each of pixel in the set (104 pixels in each set)
    for (std::vector<uint8_t>::reverse_iterator row_it = (*col_it).rbegin(); row_it != (*col_it).rend(); row_it++)
    {
      uint8_t value = *row_it;
      // If the value equals RED, it's considered TRUE otherwise FALSE
      if (value == RED)
      {
        // If RED, add one and shift left
        redValue <<= 1;
        redValue += 1;
      }
      else
      {
        // If not RED, just shift left
        redValue <<= 1;
      }
      if (value == BLACK)
      {
        // If BLACK, just shift left
        blackValue <<= 1;
      }
      else
      {
        // If not BLACK, shift left and add 1
        blackValue <<= 1;
        blackValue += 1;
      }

      if (++count == 8)
      {
        // Push the bytes into respective std::vectors
        red_buffer.push_back(redValue);
        black_buffer.push_back(blackValue);

        // Reset the bytes
        redValue = 0;
        blackValue = 0;
        count = 0;
      }
    }
  }

#ifdef DEBUG
  std::cout << "BlackBuffer Length:" << black_buffer.size() << std::endl;
  std::cout << "RedBuffer Length:" << red_buffer.size() << std::endl;
#endif

  display_update(black_buffer, red_buffer);

  display_finalise();
  return 0;
}

// Indexed using buffer[mHeight][mWidth]
// e.g buffer[x][y] or buffer[col][row]
int InkyPhat::set_pixel(int row, int column, uint8_t value)
{
  // Lock to avoid to threads attempting to set_pixels
  std::lock_guard<std::mutex> lock(mLock);

  if (row < 0 || row >= mHeight || column < 0 || column >= mWidth || value < 0 || value > 2)
  {
    return -1;
  }
  mBuffer[column][row] = value;
  return 0;
}

std::string InkyPhat::print_current_buffer()
{
  // Lock to avoid to threads attempting to update at once
  std::lock_guard<std::mutex> lock(mLock);

  std::stringstream ss;
  ss << "Current buffer values" << std::endl;

  for (int row = 0; row < mHeight; row++)
  {
    ss << "[Row:" << row << "]";
    for (int col = 0; col < mWidth; col++)
    {
      auto value = mBuffer[col][row];
      if (value == RED)
      {
        ss << "x";
      }
      else if (value == BLACK)
      {
        ss << "o";
      }
      else if (value == WHITE)
      {
        ss << "-";
      }
    }
    ss << "]" << std::endl;
  }
  return ss.str();
}

int const InkyPhat::get_width() const
{
  return mWidth;
}

int const InkyPhat::get_height() const
{
  return mHeight;
}

// Display initialisation
int InkyPhat::display_init()
{
  reset();

  send_command(0x74, 0x54); // Set analog control block
  send_command(0x75, 0x3b); // Sent by dev board but undocumented in datasheet

  // Driver output control
  std::vector<uint8_t> driverData{0xd3, 0x00, 0x00};
  send_command(0x01, driverData);

  // Dummy line period
  // Default value: 0b-----011
  // See page 22 of datasheet
  send_command(0x3a, 0x07);

  // Gate line mWidth
  send_command(0x3b, 0x04);

  // Data entry mode
  send_command(0x11, 0x03);
  return 0;
}

// Display update
int InkyPhat::display_update(std::vector<uint8_t> buf_black, std::vector<uint8_t> buf_red)
{
  std::vector<uint8_t> xRamData{0x00, 0x0c};
  send_command(0x44, xRamData); // Set RAM X address
  std::vector<uint8_t> yRamData{0x00, 0x00, 0xD3, 0x00, 0x00};
  send_command(0x45, yRamData); // Set RAM Y address + erroneous extra byte?

  std::vector<uint8_t> sourceDrivingVoltage{0x2d, 0xb2, 0x22};
  send_command(0x04, sourceDrivingVoltage); // Source driving voltage control

  send_command(0x2c, 0x3c); // VCOM register, 0x3c = -1.5v?

  // Border control
  send_command(0x3c, 0x00);
  if (mBorder == 0b11000000)
  {
    send_command(0x3c, 0x00);
  }
  else if (mBorder == 0b01000000)
  {
    send_command(0x3c, 0x33);
  }
  else if (mBorder == 0b10000000)
  {
    send_command(0x3c, 0xFF);
  }

  // VSS  = 0b00;
  // VSH1 = 0b01;
  // VSL  = 0b10;
  // VSH2 = 0b11;
  // def l(a, b, c, d):
  //     return (a << 6) | (b << 4) | (c << 2) | d;

  //// Send LUTs
  std::vector<uint8_t> lookup_tables{
      // Phase 0     Phase 1     Phase 2     Phase 3     Phase 4     Phase 5     Phase 6
      // A B C D     A B C D     A B C D     A B C D     A B C D     A B C D     A B C D
      0b01001000, 0b10100000, 0b00010000, 0b00010000, 0b00010011, 0b00000000, 0b00000000, // 0b00000000, // LUT0 - Black
      0b01001000, 0b10100000, 0b10000000, 0b00000000, 0b00000011, 0b00000000, 0b00000000, // 0b00000000, // LUTT1 - White
      0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // 0b00000000, // IGNORE
      0b01001000, 0b10100101, 0b00000000, 0b10111011, 0b00000000, 0b00000000, 0b00000000, // 0b00000000, // LUT3 - Red
      0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, // 0b00000000, // LUT4 - VCOM
      //0xA5, 0x89, 0x10, 0x10, 0x00, 0x00, 0x00, // LUT0 - Black
      //0xA5, 0x19, 0x80, 0x00, 0x00, 0x00, 0x00, // LUT1 - White
      //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // LUT2 - Red - NADA!
      //0xA5, 0xA9, 0x9B, 0x9B, 0x00, 0x00, 0x00, // LUT3 - Red
      //0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // LUT4 - VCOM

      //       Duration              |  Repeat
      //       A     B     C     D   |
      67, 10, 31, 10, 4, // 0 Flash
      16, 8, 4, 4, 6,    // 1 clear
      4, 8, 8, 32, 16,   // 2 bring in the black
      4, 8, 8, 64, 32,   // 3 time for red
      6, 6, 6, 2, 2,     // 4 final black sharpen phase
      0, 0, 0, 0, 0,     // 4
      0, 0, 0, 0, 0,     // 5
      0, 0, 0, 0, 0,     // 6
      0, 0, 0, 0, 0      // 7
  };
  send_command(0x32, lookup_tables);

  send_command(0x44, xRamData); // Set RAM X address
  std::vector<uint8_t> newYRamData{0x00, 0x00, 0xD3, 0x00};
  send_command(0x45, newYRamData); // Set RAM Y address

  send_command(0x4e, 0x00); // Set RAM X address counter
  std::vector<uint8_t> yRamAddressCounter{0x00, 0x00};
  send_command(0x4f, yRamAddressCounter); // Set RAM Y address counter

  send_command(0x24, buf_black);

  send_command(0x44, xRamData);           // Set RAM X address
  send_command(0x45, newYRamData);        // Set RAM Y address
  send_command(0x4e, 0x00);               // Set RAM X address counter
  send_command(0x4f, yRamAddressCounter); // Set RAM Y address counter

  send_command(0x26, buf_red);

  send_command(0x22, 0xc7); // Display update setting
  send_command(0x20);       // Display update activate
  usleep(50);
  busy_wait();

  return 0;
}

// Display finalisation
int InkyPhat::display_finalise()
{
  return 0;
}

int InkyPhat::busy_wait()
{
  //Wait for the e-paper driver to be ready to receive commands/data.
  int wait_for = LOW;

  while (digitalRead(mBusyPin) != wait_for)
  {
    // Yes this is a tight loop that spins waiting for a pin to change value
  }
  return 0;
}

int InkyPhat::reset()
{
  //Send a reset signal to the e-paper driver.
  digitalWrite(mResetPin, LOW);
  usleep(100);
  digitalWrite(mResetPin, HIGH);
  usleep(100);

  send_command(V2_RESET);

  busy_wait();
  return 0;
}

int InkyPhat::send_command(uint8_t command)
{
  std::vector<uint8_t> commandArray{command};
  spi_write(SPI_COMMAND, commandArray);
  return 0;
}

int InkyPhat::send_command(uint8_t command, uint8_t data)
{
  std::vector<uint8_t> commandArray{command};
  std::vector<uint8_t> dataArray{data};
  return send_command(commandArray, dataArray);
}

int InkyPhat::send_command(uint8_t command, std::vector<uint8_t> data)
{
  std::vector<uint8_t> commandArray{command};
  return send_command(commandArray, data);
}

int InkyPhat::send_command(std::vector<uint8_t> command, std::vector<uint8_t> data)
{
  spi_write(SPI_COMMAND, command);
  send_data(data);
  return 0;
}

int InkyPhat::send_data(std::vector<uint8_t> data)
{
  spi_write(SPI_DATA, data);
  return 0;
}

int InkyPhat::spi_write(uint8_t level, std::vector<uint8_t> data)
{
  digitalWrite(mCommandPin, level);
  uint8_t arr[data.size()];
  copy(data.begin(), data.end(), arr);
  wiringPiSPIDataRW(CS0_PIN, arr, data.size());
  return 0;
}