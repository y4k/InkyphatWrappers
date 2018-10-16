#include "skywriter.hpp"

Header parse_header(char bytes[])
{
    struct Header h = {.Size = bytes[0], .Sequence = bytes[2], .ID = bytes[3]};
    return h;
}

Skywriter::Skywriter() : 
    _io(),
    _guard(_io.get_executor())
{
    // Set the reset pin to an output and give it the initial value of HIGH
    pinMode(SW_RESET_PIN, OUTPUT);
    digitalWrite(SW_RESET_PIN, HIGH);

    // Set the Transfer pin to an input and configure a pull up resistor
    pinMode(SW_XFR_PIN, INPUT);
    pullUpDnControl(SW_XFR_PIN, PUD_UP);
    wiringPiISR(SW_XFR_PIN, INT_EDGE_RISING, &xfr_callback_rising);
    wiringPiISR(SW_XFR_PIN, INT_EDGE_FALLING, &xfr_callback_falling);

    // Setup i2c communication to the Skywriter
    if ( (_i2cFileHandler = wiringPiI2CSetup(SW_ADDR_1)) == -1)
    {
        #ifdef DEBUG
        std::cout << "Wiring Pi i2c setup failed:" << strerror(errno) << std::endl;
        #endif
        throw errno;
    }

    reset();

    _worker_thread = new asio::thread(
     std::bind(
       static_cast<asio::io_context::count_type (asio::io_service::*)(void)>(&asio::io_context::run),
       &_io
       )
      );
}

Skywriter::~Skywriter()
{
    _io.reset();
    _io.stop();
    _worker_thread->join();
    delete _worker_thread;
}

void Skywriter::start_process()
{
    #ifdef DEBUG
    std::cout << "Starting process" << std::endl;
    #endif

    read_once();
}

void Skywriter::end_process()
{
    #ifdef DEBUG
    std::cout << "Ending process" << std::endl;
    #endif
}

void Skywriter::xfr_callback_falling()
{
    #ifdef DEBUG
    std::cout << "Line pulled low by chip" << std::endl;
    #endif

    Skywriter &instance = Skywriter::Instance();
	asio::post(
		instance._io,
		[] { Skywriter::Instance().start_process(); });
}

void Skywriter::xfr_callback_rising()
{
    Skywriter &instance = Skywriter::Instance();
    //asio::post(instance._io, instance.end_process);
}

void Skywriter::start_transfer()
{
    #ifdef DEBUG
    std::cout << "XFR line is asserted low by the host" << std::endl;
    #endif
    
    // Take control of XFR pin
    pinMode(SW_XFR_PIN, OUTPUT);
    // Assert the pin LOW
    digitalWrite(SW_XFR_PIN, LOW);
}

void Skywriter::complete_transfer()
{
    #ifdef DEBUG
    std::cout << "XFR line is released by the host" << std::endl;
    #endif

    // Release control of transfer line
    digitalWrite(SW_XFR_PIN, HIGH);
    // Wait 300 us
    usleep(300);

    // Set the Transfer pin to an input and configure a pull up resistor
    pinMode(SW_XFR_PIN, INPUT);
    pullUpDnControl(SW_XFR_PIN, PUD_UP);
}

void Skywriter::read_once()
{
    if(digitalRead(SW_XFR_PIN) == LOW)
    {
        start_transfer();

        // Read mgc3130 i2c buffer
        unsigned char message[255];
        if(read(_i2cFileHandler, message, 255) != 255)
        {
            #ifdef DEBUG
            std::cout << "Failed to read message correctly!" << std::endl;
            #endif
            complete_transfer();
            return;
        }

        int msgSize = message[0];
        int sequence = message[2];
        int id = message[3];

        int payloadSize = int(msgSize) - 4;

        if(id > 0)
        {
            if(payloadSize > 4)
            {
                switch(id)
                {
                    case 0x91:
                        parse_sensor_data_output(msgSize, sequence, id, message+4);
                        break;
                    case 0x83:
                        parse_fw_info(msgSize, sequence, id, message+4);
                        break;
                    case 0x15:
                        parse_system_status(msgSize, sequence, id, message+4);
                        break;
                }
            }
        }
        else
        {
            std::cout << "Unknown id:" << unsigned(id) << std::endl;
        }

        complete_transfer();
    }
}

void Skywriter::reset()
{
    #ifdef DEBUG
    std::cout << "Reseting..." << std::endl;
    #endif

    digitalWrite(SW_RESET_PIN, LOW);
	usleep(100000);
	digitalWrite(SW_RESET_PIN, HIGH);
	usleep(500000);
    
    #ifdef DEBUG
    std::cout << "...Reset complete" << std::endl;
    #endif
}

void parse_sensor_data_output(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t* payload)
{
	print_header(msgSize, sequence, id);
	std::cout << "  Payload" << std::endl;

	int payloadIndex = 0;

	uint8_t dataOutCfgMask = (payload[payloadIndex+1] << 8)|payload[payloadIndex];
	int dspStatusPresent = unsigned( dataOutCfgMask & 0b1);
	int gesturePresent = unsigned( (dataOutCfgMask >> 1) & 0b1);
	int touchPresent = unsigned( (dataOutCfgMask >> 2) & 0b1);
	int airWheelPresent = unsigned( (dataOutCfgMask >> 3) & 0b1);
	int posPresent = unsigned( (dataOutCfgMask >> 4) & 0b1);
	int noisePresent = unsigned( (dataOutCfgMask >> 5) & 0b1);
	int electrode = unsigned( (dataOutCfgMask >> 8) & 0b111);
	int cic = unsigned( (dataOutCfgMask >> 11) & 0b1);
	int sdData = unsigned( (dataOutCfgMask >> 12) & 0b1);

	payloadIndex = 2;
	std::cout << std::dec
		  << "   DSPStatus:" << dspStatusPresent << std::endl
		  << "   Gesture:" << gesturePresent << std::endl
		  << "   Touch:" << touchPresent << std::endl
		  << "   AirWheel:" << airWheelPresent << std::endl
		  << "   XYZ:" << posPresent << std::endl
		  << "   Noise:" << noisePresent << std::endl
		  << "   Electrode:" << electrode << std::endl
		  << "   CIC:" << cic << std::endl
		  << "   SD:" << sdData << std::endl << std::endl

		  << "   TimeStamp:" << int(payload[payloadIndex++]) << std::endl;

	std::cout << "Index:" << payloadIndex << std::endl;
	int posValid = unsigned( payload[payloadIndex] & 0b1);
	int airWheelValid = unsigned( (payload[payloadIndex] >> 1) & 0b1);
	int rawValid = unsigned( (payload[payloadIndex] >> 2) & 0b1);
	int noiseValid = unsigned( (payload[payloadIndex] >> 3) & 0b1);
	int noiseDetected = unsigned( (payload[payloadIndex] >> 4) & 0b1);
	int clippingDetected = unsigned( (payload[payloadIndex] >> 5) & 0b1);
	int dspRunning = unsigned( (payload[payloadIndex] >> 7) & 0b1);

	std::cout << "   SystemInfo:" << std::endl
		  << "    PositionValid:" << posValid << std::endl
		  << "    AirWheelValid:" << airWheelValid << std::endl
		  << "    RawDataValid:" << rawValid << std::endl
		  << "    NoisePowerValid:" << noiseValid << std::endl
		  << "    EnvironmentNoise:" << noiseDetected << std::endl
		  << "    Clipping:" << clippingDetected << std::endl
		  << "    DSPRunning:" << dspRunning << std::endl;

	payloadIndex++;
	if(dspStatusPresent)
	{
		std::cout << "Index:" << payloadIndex << std::endl;
		std::cout
		  << "   DSPStatus:" << std::endl
		  << "    ForcedCal:" << unsigned( (payload[payloadIndex] >> 1) & 0b1) << std::endl
		  << "    StartUpCal:" << unsigned( (payload[payloadIndex] >> 2) & 0b1) << std::endl
		  << "    GestureCal:" << unsigned( (payload[payloadIndex] >> 3) & 0b1) << std::endl
		  << "    NegativeCal:" << unsigned( (payload[payloadIndex] >> 4) & 0b1) << std::endl
		  << "    IdleCal:" << unsigned( (payload[payloadIndex] >> 5) & 0b1) << std::endl
		  << "    InvalidValueCal:" << unsigned( (payload[payloadIndex] >> 6) & 0b1) << std::endl
		  << "    AFACal:" << unsigned( (payload[payloadIndex] >> 7) & 0b1) << std::endl
		  << "    TxFrequency:" << int( payload[payloadIndex+1] ) << std::endl;
		payloadIndex+=2;
	}
	if(gesturePresent)
	{
		std::cout << "Index:" << payloadIndex << std::endl;
		int gestureData = (payload[payloadIndex+3] << 24)|
				  (payload[payloadIndex+2] << 16)|
				  (payload[payloadIndex+1] << 8)|
				  (payload[payloadIndex]);
		std::cout
		  << "   GestureInfo:" << std::endl
		  << "    GestureType:" << std::endl
		  << "     None:" << int((gestureData >> 0) & 0b1) << std::endl
		  << "     Garbage:" << int((gestureData >> 1) & 0b1) << std::endl
		  << "     Flick W->E:" << int((gestureData >> 2) & 0b1) << std::endl
		  << "     Flick E->W:" << int((gestureData >> 3) & 0b1) << std::endl
		  << "     Flick S->N:" << int((gestureData >> 4) & 0b1) << std::endl
		  << "     Flick N->S:" << int((gestureData >> 5) & 0b1) << std::endl
		  << "     CircleCW:" << int((gestureData >> 6) & 0b1) << std::endl
		  << "     CircleCCW:" << int((gestureData >> 7) & 0b1) << std::endl
		  << "    GestureClass:" << int((gestureData >> 11) & 0b111) << std::endl
		  << "    EdgeFlick:" << int((gestureData >> 15) & 0b1) << std::endl
		  << "    Progress:" << int((gestureData >> 30) & 0b1) << std::endl;

		payloadIndex += 4;
	}
	if(touchPresent)
	{
		std::cout << "Index:" << payloadIndex << std::endl;
		int touchData = (payload[payloadIndex+3] << 24)|
				(payload[payloadIndex+2] << 16)|
				(payload[payloadIndex+1] << 8)|
				(payload[payloadIndex]);
		std::cout << "   TouchInfo" << std::endl
			  << "    TouchSouth:" << int( (touchData >> 0) & 0b1) << std::endl
			  << "    TouchWest:" << int( (touchData >> 1) & 0b1) << std::endl
			  << "    TouchNorth:" << int( (touchData >> 2) & 0b1) << std::endl
			  << "    TouchEast:" << int( (touchData >> 3) & 0b1) << std::endl
			  << "    TouchCenter:" << int( (touchData >> 4) & 0b1) << std::endl
			  << "    TapSouth:" << int( (touchData >> 5) & 0b1) << std::endl
			  << "    TapWest:" << int( (touchData >> 6) & 0b1) << std::endl
			  << "    TapNorth:" << int( (touchData >> 7) & 0b1) << std::endl
			  << "    TapEast:" << int( (touchData >> 8) & 0b1) << std::endl
			  << "    TapCenter:" << int( (touchData >> 9) & 0b1) << std::endl
			  << "    DoubleTapSouth:" << int( (touchData >> 10) & 0b1) << std::endl
			  << "    DoubleTapWest:" << int( (touchData >> 11) & 0b1) << std::endl
			  << "    DoubleTapNorth:" << int( (touchData >> 12) & 0b1) << std::endl
			  << "    DoubleTapEast:" << int( (touchData >> 13) & 0b1) << std::endl
			  << "    DoubleTapCenter:" << int( (touchData >> 14) & 0b1) << std::endl

			  << "    TouchCounter:" << int( (touchData >> 15) & 0b11111111) * 5 << std::endl;

		payloadIndex+=4;
	}
	if(airWheelPresent)
	{
		std::cout << "Index:" << payloadIndex << std::endl;
		int airWheelData = payload[payloadIndex];

		std::cout << "   AirWheelInfo" << std::endl
			  << "    Progression:" << airWheelData << std::endl;

		payloadIndex += 2;
	}
	if(posPresent)
	{
		std::cout << "Index:" << payloadIndex << std::endl;
		int xPosData = (payload[payloadIndex+1] << 8)|payload[payloadIndex];
		int yPosData = (payload[payloadIndex+3] << 8)|payload[payloadIndex+2];
		int zPosData = (payload[payloadIndex+5] << 8)|payload[payloadIndex+4];

		std::cout << "   PositionInfo" << std::hex << "(" << xPosData << "," << yPosData << "," << zPosData << ")" << std::endl
			  << "    X:" << std::dec << xPosData << std::endl
			  << "    Y:" << yPosData << std::endl
			  << "    Z:" << zPosData << std::endl;

		payloadIndex+=6;
	}
	if(noisePresent)
	{
		std::cout << "Index:" << payloadIndex << std::endl;

		int noiseValue = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 

		std::cout << "   NoisePower:" << noiseValue << std::endl;

		payloadIndex+=4;
	}
	if(cic)
	{
		std::cout << "Index:" << payloadIndex << std::endl;

		int southCic = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 
		payloadIndex+=4;
		int westCic = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 
		payloadIndex+=4;
		int northCic = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 
		payloadIndex+=4;
		int eastCic = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 

		std::cout << "   CICData:" << std::endl
			  << "    South:" << float(southCic) << std::endl
			  << "    West:" << float(westCic) << std::endl
			  << "    North:" << float(northCic) << std::endl
			  << "    East:" << float(eastCic) << std::endl;
		if(electrode)
		{
			payloadIndex+=4;
			int centerCic = (payload[payloadIndex+3] << 24)|
				      (payload[payloadIndex+2] << 16)|
			   	      (payload[payloadIndex+1] << 8)|
				      payload[payloadIndex]; 
			std::cout << "    Center:" << float(centerCic) << std::endl;
		}
		payloadIndex+=4;
	}
	if(sdData)
	{
		std::cout << "Index:" << payloadIndex << std::endl;
		
		int southSd = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 
		payloadIndex+=4;
		int westSd = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 
		payloadIndex+=4;
		int northSd = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 
		payloadIndex+=4;
		int eastSd = (payload[payloadIndex+3] << 24)|
				 (payload[payloadIndex+2] << 16)|
				 (payload[payloadIndex+1] << 8)|
				 payload[payloadIndex]; 

		std::cout << "   SDData:" << std::endl
			  << "    South:" << float(southSd) << std::endl
			  << "    West:" << float(westSd) << std::endl
			  << "    North:" << float(northSd) << std::endl
			  << "    East:" << float(eastSd) << std::endl;
		if(electrode)
		{
			payloadIndex+=4;
			int centerSd = (payload[payloadIndex+3] << 24)|
				      (payload[payloadIndex+2] << 16)|
			   	      (payload[payloadIndex+1] << 8)|
				      payload[payloadIndex]; 
			std::cout << "    Center:" << float(centerSd) << std::endl;
		}
		payloadIndex+=4;
    }
}

void parse_system_status(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t* payload)
{
	print_header(msgSize, sequence, id);
	std::cout << "  Payload" << std::endl;
	std::cout << "   MsgId:     " << std::hex << int(payload[0]) << std::endl
		  << "   MaxCmdSize:" << std::hex << int(payload[1]) << std::endl
		  << "   ErrorCode: " << std::hex << combine_bytes(2, payload + 2) << std::endl;
}

void parse_fw_info(uint8_t msgSize, uint8_t sequence, uint8_t id, uint8_t* payload)
{
	print_header(msgSize, sequence, id);
	std::cout << "  Payload" << std::endl;
	std::cout << "   FwValid:             " << std::hex << int(payload[0]) << std::endl
		  << "   HwRev:               " << std::dec << int(payload[1]) << "." << int(payload[2]) << std::endl
		  << "   ParameterStartAddr:  " << std::hex << int(payload[3]) << std::endl
		  << "   LibraryLoaderVersion:" << std::dec << int(payload[4]) << "." << int(payload[5]) << "." << int(payload[6]) << std::endl
		  << "   FwStartAddr:         " << std::hex << int(payload[7]) << std::endl
		  << "   FwVersion:           ";
	for(int i = 0;i < 120;i++)
	{
		std::cout << payload[8 + i];
	}
	std::cout << std::endl;
}

void print_header(uint8_t msgSize, uint8_t sequence, uint8_t id)
{
	std::cout << "New Message" << std::endl
	          << "  MsgSize:" << std::hex << unsigned(msgSize) << std::endl
	          << "  Sequence:" << std::dec << unsigned(sequence) << std::endl
	          << "  ID:" << std::hex << unsigned(id) << std::endl;
}

int combine_bytes(int numBytes, uint8_t* bytes)
{
	if(numBytes < 1)
	{
		return -1;
	}

	int current = 0;
	for(int i = 0;i < numBytes;i++)
	{
		current = (current << 8)|bytes[i];
	}
	return current;
}