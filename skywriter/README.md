# Skywriter

## Messages

* Payload elements of messages are LITTLE ENDIAN. Lowest Significant Byte first.
* Read messages as a series of hexadecimal values.
  * First four values are the header.
    1. Size - size of the message including the header
    2. Flags - UNUSED
    3. Seq - Sequence number. Ignore messages that appear out of sequence
    4. ID - Message ID. Match against the constants below to determine the message type
* Remainder of the message is the payload.

### System Status

Message Direction: *Chip to Host*

The system status message is used to acknowledge the receipt of messages from the host. The message holds the error code and is used to confirm transmission of the following:

* Request Message (0x06)
* Set Runtime Parameter (0xA2)
* Firmware Update Start (0x80)
* Firmware Update Block(0x81)
* Firmware Update Completed (0x82)

#### Header

|Message Size|Flags|Sequence|ID|
|---|---|---|---|
|1 Byte|1 Byte|1 Byte|1 Byte|
|0x10| n/a|n/a|0x15|

#### Payload

|Message ID|Max Command Size|Error Code|*Reserved*|*Reserved*|
|---|---|---|---|---|---|
|1 Byte|1 Byte|2 Bytes|4 Bytes|4 Bytes|
|The message ID that this response corresponds to.<br> **Range**:(0x00..0xFF)|Max I2C packet size accepted by GestIC Library.<br> **Range**:(0..0xFF)||