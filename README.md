# InkyphatWrappers

Wrappers for:

1) Inkyphat from [Pimoroni](https://shop.pimoroni.com/products/inky-phat)
2) Blinkt from [Pimoroni](https://shop.pimoroni.com/products/blinkt)

When used on a Raspberry Pi, requires the [wiringPi library](http://wiringpi.com/download-and-install/)

Requires the SPI interface to be enabled in order to run on a Raspberry Pi. Will also require either running with root access or by adding the desired user to the ```gpio``` and ```spi``` groups.

```bash
sudo adduser <username> gpio
sudo adduser <username> spi
```