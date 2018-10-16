# Skywriter

## Message Control Flow

* Control of the chip is done through the *Set Runtime Parameter* and *Request Message* messages. Both messages are acknowledged by the chip using a *System Status* message containing the original message ID and a 2-byte error code.
* If the error code is *0* then the message was applied successfully.
* Read messages as a series of hexadecimal values.

## Message Format

* Minimum Length is 4 bytes.
* Maximum length is 255 bytes.
* Each frame is a **single** message.
* First four values are the header.
* Remainder of the message is the payload.

### Message Header

|Field|Size (bytes)|Description|
|---|---|---|
|Msg. Size|1||Complete size of the message in bytes including the header|
|Flags|1|Reserved for future use|
|Sequence|1|Sequence number which is increased for each message sent out by the chip.<br>Range(0..255)<br>The chip ignores the sequence number in receieved messages. |
|ID|1|ID of the message. For each ID, the library holds a structure containing the <br>message direction, its payload elements and possible reply actions|

### Message Payload

* Payload elements of messages are LITTLE ENDIAN. Lowest Significant Byte first.

## System Control

|ID|Name|
|---|---|
|0x15|System Status|
|0x06|Request Message|
|0x83|FW Version Info|
|0xA2|Set Runtime Parameter|

### System Status

Message Direction: *Chip to Host*

The system status message is used to acknowledge the receipt of messages from the host. The message holds the error code and is used to confirm transmission of the following:

| Message | ID |
| :--- |  ---:|
| Request Message | (0x06)|
| Set Runtime Parameter | (0xA2)|
| Firmware Update Start | (0x80)|
| Firmware Update Block | (0x81)|
| Firmware Update Completed | (0x82)|

Once acknowledged, if the error code is **0** then the message was applied correctly.

#### Header

|Message Size|Flags|Sequence|ID|
|---|---|---|---|
|1 Byte|1 Byte|1 Byte|1 Byte|
|0x10| n/a|n/a|0x15|

#### Payload

|Message ID|Max Command Size|Error Code|*Reserved*|*Reserved*|
|---|---|---|---|---|---|
|1 Byte|1 Byte|2 Bytes|4 Bytes|4 Bytes|
|The message ID that this response corresponds to.<br> **Range**:(0x00..0xFF)|Max I2C packet size accepted by GestIC Library.<br> **Range**:(0..0xFF) | Error code returned for the previous message. 16-bit word (see table below)|n/a|n/a|

##### Library Loader, Library Loader Updater and Library Error Codes

|Code|Reason|
|---|---|
|0x0000 NoError| OK |
|0x0001 UnknownCommand| MessageID is unknown |

##### Library Loader Error Codes

|Code|Reason|
|---|---|
|0x0002 InavalidSessionId | Session ID is invalid or does not match (0x0 is not allowed) |
|0x0003 InvalidCrc | CRC is invalid. Thrown by FwUpdateBlock, FwUpdateStart, FwUpdateCompleted |
|0x0004 InvalidLength | Length is invalid. Thrown by FwUpdateBlock |
|0x0005 InvalidAddress | Address is invalid. Thrown by FwUpdateBlock |
|0x0006 InvalidFunction | Function ID is invalid. Thrown by FwUpdateStart, FwUpdateBlock, FwUpdateCompleted |
|0x0007 ContentMismatch | The *VerifyOnly* function found a mismatch between content and Flash memory. Thrown by FwUpdateBlock |
|0x0008 WrongParameterAddr | Parameter Start address contained in the new Library FW to be loaded does not match Library Loader assumption. The Library Update is therefore aborted. Thrown by FwUpdateStart |

##### Library Error Codes

|Code|Reason|
|---|---|
|0x0014 WrongParameterValue | The value of the Argument/Parameter of a RuntimeParameter command is out of the valid range. Thrown by Request Message, Set_Runtime_Parameter
|0x0015 UnknownParameterID | The MessageID or RuntimeParameterID is unknown or out of the valid range. Thrown by Request Message, Set_Runtime_Parameter.
|0x001A WakeupHappend | A wake-up by Host was detected|

##### Library Loader Updater Error Codes

|Code|Reason|
|---|---|
|0x0080 LoaderUpdateStarted | The Library Loader update started|
|0x0081 LoaderUpdateFinished |The Library Loader update finished|

### Request Message

Message Direction: *Host to chip*

Forces the chip to respond to the message with the requested ID.

#### Header

|Message Size|Flags|Sequence|ID|
|---|---|---|---|
|1 Byte|1 Byte|1 Byte|1 Byte|
|0x0C| n/a|n/a|0x06|

#### Payload

|Message ID| Reserved | Parameters|
|---|---|---|
|1 Byte|3 Bytes|4 Bytes|
|**Range**(0x00..0xFF)<br> Only works with *0x83* (FW Version Info) and *0xA2*(Set Runtime Parameter)|Reserved. Write as *0*|Optional parameter to specify the kind of return. 32-bit word.<br>**Range**(0x00000000..0xFFFFFFFF)|

Note. TransFreqSelect runtime parameter is write-only and could not be requested with *Request Message*

### FW Version Info

Message Direction: Chip to Host

At start up, the chip sends the firmware version info message to the host to show that the chip is alive and ready for operation. Can be requested using *Request Message (0x06)*.

#### Header

|Message Size|Flags|Sequence|ID|
|---|---|---|---|
|1 Byte|1 Byte|1 Byte|1 Byte|
|0x84| n/a|n/a|0x83|

#### Payload

|FW Valid| HwRev | ParameterStartAddr | LibraryLoaderVersion | FwStartAddr | FwVersion |
|---|---|---|---|---|---|
|1 Byte|2 Bytes|1 Byte|3 Bytes|1 Byte|120 Bytes|
| Library status.<br> 0x00 Empty - No valid library <br>0x0A InvalidFW - Invalid library or update failed<br>0xAA Valid FW | Hardware revision.<br> **Format** xx.xx<br>**Range**(0x00..0xFF,0x00..0xFF) | Parameter start address as supported by the image address. 128 * value of ParameterStartAddr <br>**Range**(0x00..0xFF)| Loader version info. <br> **Format**xx.xx.xx<br>**Range**(0x00..0xFF,0x00..0xFF,0x00..0xFF) | Start address of GestIC ® Library as supported by the Bootloader, start address = 128 * value of FwStartAddr <br>**Range**(0x00..0xFF) | Firmware version if valid. Semi-colon separated. Interpret as ASCII. Starts with version number. |

## Sensor Data

|ID|Name|
|---|---|
|0x91|Sensor Data Output|

## Library Update

|ID|Name|
|---|---|
|0x80|FW Update Start|
|0x81|FW Update Block|
|0x82|FW Update Completed|

## Notes

* Whilst the MGC3130 chip does use I2C to communicate, it was found that the WiringPi library could not read buffers of sufficient size in one transaction. That is why it has been used to initialise the I2C interface but standard *read* and *write* calls are used as opposed to *wiringPiI2CReadReg8* etc.