#include "Arduino.h"
#include "Tugboat.h"
#include <Array.h> //https://github.com/jshaw/arduino-array

Tugboat::Tugboat()
{

}

// FUNCTIONS =================================================================
void Tugboat::init() {
  // SENSE
  pixy.init();
  senseir.init();
  // ACT
  propellor.attach(propellorPin);
  propellor.writeMicroseconds(1500);
  rudder.attach(rudderPin);
  rudder.writeMicroseconds(1500);
}
// Sense Functions -----------------------------------------------------------
void Tugboat::updatePixy() {
  Serial.println("Attempting to update Pixy");
  //Pixy target detection
  int blocks = pixy.getBlocks();

  if(blocks)
  {
    Serial.println("Blocks found!");
    int targetrange = sensepixy.getTargetRange(pixy,blocks);
    sensepixy.getTargetBearing(pixyDataArray,NUM_PTS,pixy,blocks,targetrange,1); // 1 is gaussian distribution    
  }
}
void Tugboat::updateIR(){
  senseir.updateIRData(irDataArray);
}

// Think Functions -----------------------------------------------------------
void Tugboat::stateController() {
  switch (state) {
      case 1: Serial.println("Robot State: stop");
              stop();
              break;
      case 2: Serial.println("Robot State: idle");
              idle();
              break;
      case 3: Serial.println("Robot State: chase");
              chase();
              break;
      case 4: Serial.println("Robot State: search");
              search();
              break;
      default: Serial.println("Robot State: stop *WARNING* Invalid Input");
               stop();
               break;
  }
}

void Tugboat::stop() {
  cmd_heading = 0;
  cmd_velocity = 0;
}
void Tugboat::idle() {
  cmd_velocity = 0;
}
void Tugboat::chase() {
  cmd_heading = heading;
  cmd_velocity = velocity;
}
void Tugboat::search() {
  cmd_heading = heading;
  cmd_velocity = velocity;
}
/*
void processData() { // Takes irDataArray, pixyDataArray as input. Modifies irDecisionArray, pixyDecisionArray
  return;
}
*/
void Tugboat::arbiter() { // Takes irDecisionArray, pixyDecisionArray, state as input. Modifies heading, velocity, and state
  
  Array<int> decisionArray = Array <int>(pixyDataArray,NUM_PTS); //TODO: Make this take sum of pixyDecisionArray and irDecisionArray
  
  int max_val = decisionArray.getMax();
  int max_index;
  
  for (int i=0; i<NUM_PTS; i++) {
     if (max_val == decisionArray[i]) {
       max_index = i;
       break;
     }
  }
  
  velocity = max_val*5; // TODO: Parameterize this and make speed between -100 and 100
  heading = max_index*10 - 170; // TODO: Parameterize this to work with any number of NUM_PTS

}

// Act Functions -------------------------------------------------------------

//function to set propellor speed by percentage
void Tugboat::setPropSpeed(int speedPercentage){
  // Boat speed is between 1000 and 2000 with 1500 = boat stopped
  int microSec;
  if (speedPercentage>=100){ // Limit max speed percentage
    microSec= 2000;        //full speed forward
  }
  else if (speedPercentage<100 && speedPercentage>-100){
    microSec = map(speedPercentage,-100, 100, 1000, 2000);
  }
  else if (speedPercentage<=-100){ // Limit min speed percentage
    microSec=1000;         // back up full speed
  }
  propellor.writeMicroseconds(microSec);
}


void Tugboat::setHeading(int degHeading) // Input heading in degrees
{
  // Boat heading is between -45 degrees (left) and 45 degrees (right), which maps to 1000 to 2000 microseconds with 1500 = 0 degrees
  int microSec;
  if (degHeading>=45){ // Limit max turn right
    microSec= 2000;        // max right turn
  }
  else if (degHeading<45 && degHeading>-45){
    microSec = map(degHeading,-45, 45, 1000, 2000);
  }
  else if (degHeading<=-45){ // Limit max turn left
    microSec=1000;         // max left turn
  }
  rudder.writeMicroseconds(microSec);
}

// move(heading, velocity)
