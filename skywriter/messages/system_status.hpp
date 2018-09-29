#ifndef SW_MSG_SYSTEM_STATUS_H
#define SW_MSG_SYSTEM_STATUS_H

// SYSTEM STATUS Message Definition

// Header
#define SW_MSG_SYSTEM_STATUS_SIZE 0x10      // Message Size
#define SW_MSG_SYSTEM_STATUS_ID 0x15        // Message ID

// Payload
#define SW_MSG_SYSTEM_STATUS_PAYLOAD_ITEMS 5
#define SW_MSG_SYSTEM_STATUS_PAYLOAD_FORMAT (1,1,2,4,4)

// Errors from Library, Library Loader and Library Loader Updater
#define SW_MSG_SYSTEM_STATUS_ERR_NOERROR 0x0000                 // No Error
#define SW_MSG_SYSTEM_STATUS_ERR_UNKCMD 0x0001                  // Unknown command

// Errors from Library Loader
#define SW_MSG_SYSTEM_STATUS_ERR_INVALIDSESSIONID 0x0002        // Invalid session ID
#define SW_MSG_SYSTEM_STATUS_ERR_INVALIDCRC 0x0003              // Invalid CRC
#define SW_MSG_SYSTEM_STATUS_ERR_INVALIDLENGTH 0x0004           // Invalid length
#define SW_MSG_SYSTEM_STATUS_ERR_INVALIDADDR 0x0005             // Invalid address
#define SW_MSG_SYSTEM_STATUS_ERR_INVALIDFUNC 0x0006             // Invalid function
#define SW_MSG_SYSTEM_STATUS_ERR_CONTENTMISMATCH 0x0008         // Content mismatch
#define SW_MSG_SYSTEM_STATUS_ERR_WRGPRMADDR 0x000B              // Wrong parameter address
#define SW_MSG_SYSTEM_STATUS_ERR_WRGPRMVAL 0x0014               // Wrong parameter value
#define SW_MSG_SYSTEM_STATUS_ERR_UNKPRMID 0x0015                // Unknown parameter ID
#define SW_MSG_SYSTEM_STATUS_ERR_WAKEUPHPD 0x001A               // Wake up happened

// Errors from Library Loader Updater
#define SW_MSG_SYSTEM_STATUS_ERR_LDRUPDSTRT 0x0080              // Loader update started
#define SW_MSG_SYSTEM_STATUS_ERR_LDRUPDFIN 0x0081               // Loader update finished

#endif