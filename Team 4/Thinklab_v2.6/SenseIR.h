#ifndef SenseIR_h
#define SenseIR_h

#include "Arduino.h"
#include "Pixy.h"
#include "SPI.h"


class SenseIR
{
  public:
  
    SenseIR();
    void init();
    void updateIRData(int shiftedDistanceValues[]);
   
    // TODO: Reclassify these as public or private more sensibly, remove hardcode
    // define sensor setups
    int irPins [5] = {0, 1, 2, 3, 4};
    int irHeadings[5] = {0, 4, 9, 27, 32}; //locations of IR sensors in 10s of degrees
    int irData[35];
    int distanceValues[35];
    
    
    int irPinSize   = sizeof(irPins) / sizeof(int);
    int irDataSize  = sizeof(irData) / sizeof(int);
    
    // define sensor counts to take for averaging
    int counts = 20;
    
    // type of each IR sensor, in order corresponding to pins and headings
    int irTypes[5] = {1, 1, 1, 1, 1}; //1 = short, 2 = medium, 3 = long
    
    int lowSensorHeading;
    int lowSensorReading;
    int highSensorHeading;
    int highSensorReading;
    bool headingHasIR; 


  private:
    int sensorRead(int sensorPin);
    int IRtoDistance(int rawData, int sensorType);
    int shortIRtoDistance(int input);
    int medIRtoDistance(int input);
    int longIRtoDistance(int input);
};
    
#endif
