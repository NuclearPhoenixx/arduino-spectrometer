/*
 * Simple Arduino spectrometer.
 */

#include "Adafruit_AS726x.h"

//create the object
Adafruit_AS726x ams;

//buffer to hold raw values
//uint16_t sensorValues[AS726x_NUM_CHANNELS];

//buffer to hold calibrated values (not used by default in this example)
float calibratedValues[AS726x_NUM_CHANNELS];

void setup()
{
  Serial.begin(57600); //start fast Serial
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin()){
    Serial.println("Error, no sensor!");
    while(1);
  }

  ams.setIndicateCurrent(LIMIT_1MA); //set current for indicator LED 1mA
  ams.indicateLED(false); //turn on indicator LED
  
  ams.setDrvCurrent(LIMIT_12MA5); //LIMIT_12MA5, LIMIT_25MA, LIMIT_50MA, or LIMIT_100MA
  
  ams.drvOff(); //turn off drive LED
  //ams.drvOn();
  
  ams.setConversionType(MODE_2); //MODE_0, MODE_1, MODE_2, ONE_SHOT
  ams.setGain(GAIN_64X); //GAIN_1X, GAIN_3X7, GAIN_16X, or GAIN_64X
  ams.setIntegrationTime(50); //actual integration time will be time*2.8ms
  
}

void loop()
{
  //read the device temperature
  uint8_t temp = ams.readTemperature();
  
  ams.startMeasurement(); //begin a measurement
  
  //wait till data is available
  bool ready = false;
  while(!ready)
  {
    delay(5);
    ready = ams.dataReady();
  }

  //read the values!
  //ams.readRawValues(sensorValues);
  ams.readCalibratedValues(calibratedValues);

  /*
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" Violet: "); Serial.print(sensorValues[AS726x_VIOLET]);
  Serial.print(" Blue: "); Serial.print(sensorValues[AS726x_BLUE]);
  Serial.print(" Green: "); Serial.print(sensorValues[AS726x_GREEN]);
  Serial.print(" Yellow: "); Serial.print(sensorValues[AS726x_YELLOW]);
  Serial.print(" Orange: "); Serial.print(sensorValues[AS726x_ORANGE]);
  Serial.print(" Red: "); Serial.print(sensorValues[AS726x_RED]);

  Serial.println();
  Serial.println();
  */

  // VBGYOR
  //Serial.print("TEMP: "); Serial.print(temp);
  //Serial.print(" | V: ");
  Serial.print(calibratedValues[AS726x_VIOLET]); Serial.print(", ");
  //Serial.print(" | B: ");
  Serial.print(calibratedValues[AS726x_BLUE]); Serial.print(", ");
  //Serial.print(" | G: ");
  Serial.print(calibratedValues[AS726x_GREEN]); Serial.print(", ");
  //Serial.print(" | Y: ");
  Serial.print(calibratedValues[AS726x_YELLOW]); Serial.print(", ");
  //Serial.print(" | O: ");
  Serial.print(calibratedValues[AS726x_ORANGE]); Serial.print(", ");
  //Serial.print(" | R: ");
  Serial.print(calibratedValues[AS726x_RED]);
  
  //Serial.println();
  Serial.println();
  //Serial.println();
  //Serial.println();

  delay(5000);
}
