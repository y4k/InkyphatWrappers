// I2C address
#define ADDR_1 0x42
#define ADDR_2 0x43

// GPIO pins - Broadcom numbering scheme used
#define TRFR_PIN 27
#define RESET_PIN 17
#define SCL_PIN 3
#define SDA_PIN 2

// Skywriter system control messages
#define SW_SYSTEM_STATUS 0x15
#define SW_REQUEST_MESSAGE 0x06
#define SW_FW_VERSION_INFO 0x83
#define SW_SET_RUNTIME_PARAMETER 0xA2

// Skywriter sensor data output messages
#define SW_SENSOR_DATA 0x91

// Skywriter library update messages
#define SW_FW_UPDATE_START 0x80
#define SW_FW_UPDATE_START 0x81
#define SW_FW_UPDATE_START 0x82

//Additional constants
#define MSG_HEADER_SIZE 4 // Number of bytes