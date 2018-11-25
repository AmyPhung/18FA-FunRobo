#include "SenseIR.h"

SenseIR::SenseIR() 
{  
}

void SenseIR::init() {
  //TODO: set up i2c communication
  Serial.begin(9600);


  // set each IR pin to input
  for (int i = 0; i < irPinSize; i++){
    pinMode(i, INPUT);
  }

  // initialize variables
  // fill irData with 0s
  for (int i = 0; i < irDataSize; i++){
    irData[i] = 0;
    distanceValues[i] = 0;
  }
}

void SenseIR::updateIRData(int distanceValues[]) {
  

  // read data from each sensor
  for (int i = 0; i < irPinSize; i++){
    // read sensor data from specified pin, then insert data directly to 
    // the sensor's heading (which is also the index in irData)
    irData[ irHeadings[i] ] = sensorRead(irPins[i]);
  }


// DEBUGGING: PRINT SENSOR READINGS TO SERIAL
//  for (int i = 0; i < irDataSize; i++){
//    Serial.print(irData[i]);
//    Serial.print("\t");
//  }
//  Serial.println();


  // convert sensor data to distance
  // floor to in in nearest cm
  for (int i = 0; i < irPinSize; i++){
    // look at sensor data in array
    // check to see what type of sensor it is, then convert to cm
    int rawSensorData = irData[ irHeadings[i] ];
    int sensorType = irTypes[i];
    distanceValues[ irHeadings[i] ] = IRtoDistance(rawSensorData, sensorType);
  }


// DEBUGGING: PRINT DISTANCE VALUES TO SERIAL
//  for (int i = 0; i < irDataSize; i++){
//    Serial.print(distanceValues[i]);
//    Serial.print("\t");
//  }
//  delay(20);
//  Serial.println();
//  Serial.println();


  // CREATE BETTER DISTANCE ARRAY
  // add interpolation between values
  // for filler headings in our array, interpolate the value from the lower sensor and upper sensor values and headings
  for (int currentHeading = 0; currentHeading < irDataSize; currentHeading++){
    headingHasIR = false; //assume heading doesn't have IR
//    Serial.print("current heading to check: ");
//    Serial.print(currentHeading);
//    Serial.print("\t");
//    
    // check if current heading is in our list of sensor headings
    for (int j = 0; j < irPinSize; j++){
      if (currentHeading == irHeadings[j]){
        headingHasIR = true;
        break;
      }
    } 

    if (headingHasIR){ 
        //if the current heading is in our list of headings with IR
        //dont modify its value, but change our sensor heading frame
        // set current sensor heading to the lowSensorHeading
        
        lowSensorHeading = currentHeading;
        lowSensorReading = distanceValues [currentHeading];
        
//        Serial.print(currentHeading);
//        Serial.print("\t");
//        Serial.println("in list");
        
        // update high sensor heading HARDCODED
        if (lowSensorHeading = 9) highSensorHeading = 13;
        else if (lowSensorHeading = 13) highSensorHeading = 18;
        else if (lowSensorHeading = 18) highSensorHeading = 23;
        else if (lowSensorHeading = 23) highSensorHeading = 27;
        else if (lowSensorHeading = 27) highSensorHeading = 9;
  
        highSensorReading = distanceValues [highSensorHeading];
      }
      else if (currentHeading < 9 or currentHeading > 27){
        // hardcode to 20, these are headings that we are blind to
        distanceValues[currentHeading] = 30;
        
//        Serial.print(currentHeading);
//        Serial.print("\t");
//        Serial.println("blind heading");
      }
      else {
        distanceValues[currentHeading] = abs(map(currentHeading, lowSensorHeading, highSensorHeading, lowSensorReading, highSensorReading));
//        Serial.print(currentHeading);
//        Serial.print("\t");
//        Serial.println("mapped heading");
      } 
    

    
  }  

  // DEBUGGING: PRINT SHIFTED DISTANCE VALUES TO SERIAL
//  for (int i = 0; i < irDataSize; i++){
//    if (i > 8 and i < 28){
//      Serial.print(i);
//      Serial.print(": ");
//      Serial.print(shiftedDistanceValues[i]);
//      Serial.print("\t");
//    }
//  }
//  Serial.println();
//  Serial.println();



  // send distance array over i2c


  // DEBUGGING: PRINT DISTANCE VALUES TO SERIAL
  for (int i = 0; i < irDataSize; i++){
    if (i > 8 and i < 28){
      Serial.print(i);
      Serial.print(": ");
      Serial.print(distanceValues[i]);
      Serial.print("\t");
    }
  }
  Serial.println();
  Serial.println();



  //TODO: send distance array over i2c

}




// Private Functions:
int SenseIR::sensorRead(int sensorPin){
  //average sensor reading 
  int reading = 0;
  int cumReading = 0;
  int avgReading = 0;
  
  for (int i = 0; i < counts; i++){
    reading = analogRead(sensorPin);
    cumReading = reading + cumReading;
    delay(1);
  }
  
  avgReading = cumReading / counts;
  return avgReading;
}


int SenseIR::IRtoDistance(int rawData, int sensorType){

  int distanceData = 0;
    
  switch (sensorType) {
    case 1: //short
      distanceData = shortIRtoDistance(rawData);
      break;
    case 2: //medium
      distanceData = medIRtoDistance(rawData);
      break;
    case 3: //long
      distanceData = longIRtoDistance(rawData); 
      break;    
  }

  return distanceData;
}


int SenseIR::shortIRtoDistance(int input){
  input = constrain(input, 75, 500);
  int distance = 2556.5 * pow(input, -1.0161);
  return distance;
}

int SenseIR::medIRtoDistance(int input){
  input = constrain(input, 130, 645);
  int distance = 18110 * pow(input, -1.2148);
  return distance;
}

int SenseIR::longIRtoDistance(int input){
  input = constrain(input, 150, 400);
  int distance = 19807 * pow(input, -1.0917);
  return distance;
}
