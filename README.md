# Arduino Spectrometer
Simple 6-Channel spectrometer using the AS7262 visible light spectral sensor.

The spectrometer collects the calibrated values of each color channel and returns them via a serial connection with an optional sensor temperature output.
All data is CSV formatted and therefore can be processed quite easily.

Channels and data include (in measuring order) violet, blue, green, yellow, orange and red (VBGYOR).

Settings include turning the bright, white driver LED on and off; the type of return data (absolute or relative values); the measurement interval and turning on/off the optional temperature log.

Standard Serial Connection is established with a baud rate of 57600!

**Data is printed as follows:**

```
V,B,G,Y,O,R(,temp)
```