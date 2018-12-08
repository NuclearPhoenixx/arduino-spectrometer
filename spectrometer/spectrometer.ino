/*
 * Simple Arduino spectrometer.
 * Return all data serial in csv format ready to be saved.
 * Can be used to return relative or absolute values.
 */
#include "Adafruit_AS726x.h"

/* SETTINGS */
#define INTERVAL 2000 //measurement interval in ms
#define REL_VALUES true //true returns relative values, false absolute values
#define DRV_LED true //turn on (true) / off (false) the driver LED

//create ams library object
Adafruit_AS726x ams;

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin())
  {
    Serial.println("Error, no sensor!");
    while(1);
  }

  ams.setIndicateCurrent(LIMIT_1MA); //set current for indicator LED 1mA
  ams.indicateLED(false); //turn on indicator LED
  
  ams.setDrvCurrent(LIMIT_12MA5); //LIMIT_12MA5, LIMIT_25MA, LIMIT_50MA, or LIMIT_100MA

  //control the driver led
  if(DRV_LED) { ams.drvOn(); } else { ams.drvOff(); }
  
  ams.setConversionType(MODE_2); //MODE_0, MODE_1, MODE_2, ONE_SHOT
  ams.setGain(GAIN_64X); //GAIN_1X, GAIN_3X7, GAIN_16X, or GAIN_64X
  ams.setIntegrationTime(50); //actual integration time will be time*2.8ms

  Serial.begin(57600); //start fast Serial
}

void loop()
{
  //buffer to hold calibrated values
  float calibratedValues[AS726x_NUM_CHANNELS];
  
  //read the device temperature
  uint8_t temp = ams.readTemperature();
  
  ams.startMeasurement(); //begin measurement
  
  //wait for the sensor to be ready
  bool ready = false;
  while(!ready)
  {
    delay(5);
    ready = ams.dataReady();
  }

  //read the temperature corrected color channels
  ams.readCalibratedValues(calibratedValues);
  uint8_t arraySize = sizeof(calibratedValues)/sizeof(float);

  if(REL_VALUES)
  {
    float sumValue = 0;
    
    for(uint8_t i = 0; i < arraySize; i++) //add all the channel values
    {
      sumValue += calibratedValues[i];
    }

    for(uint8_t i = 0; i < arraySize; i++) //compute the ratio of every channel
    {
      calibratedValues[i] /= sumValue;
    }
  }

  // VBGYOR
  for(uint8_t i = 0; i < arraySize; i++)
  {
    Serial.print(calibratedValues[i]);
    
    if(i < arraySize - 1) //add comma and blank after every value except the last one
    {
      Serial.print(", ");
    }
  }

  Serial.println();
  delay(INTERVAL);
}
