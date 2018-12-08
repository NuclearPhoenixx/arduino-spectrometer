# Arduino Spectrometer
Simple 6-Channel spectrometer using the AS7262 visible light spectral sensor.

The spectrometer collects the temperature calibrated values of each color channel and returns them via a serial connection.
All data is csv formatted and therefore can be processed easily.

Channels and data include (in measuring order) violet, blue, green, yellow, orange and red (VBGYOR).

Settings include turning the bright, white driver LED on and off; the type of return data (absolute or relative values) and the measurement interval.

Standard Serial Connection is established with a baud rate of 57600!
