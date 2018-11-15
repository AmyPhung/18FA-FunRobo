/*
Pseudocode:
TO TEST: input some data, print desired heading

globals:
heading
velocity
state

weights: (used for determining how important it is)
ir_const (map 0-200 to 0-1)
pixy_const (map to 0-1)

data:
irDataArray - should be standard length [35] (data in cm, ranges from 0 to 200cm)
pixyDataArray - should be standard length [35]

decision:
irDecisionArray - irDataArray * ir_const
pixyDecisionArray

void processData(all data arrays)
//PROCESS IR

//PROCESS PIXY

void arbiter(all decision arrays, current state):
Params: all data, current state
heading = max(decisionArray)
velocity = decisionArray[max_val] * some scaling factor (make this between 0 and 1)
Output: heading, velocity, state
*/


#include "Tugboat.h"
#include "SenseTarget.h"


Tugboat boat;

//========================================================================================
// Create and initialize global variables, objects and constants (containers for all data)
//========================================================================================
boolean realTimeRunStop = true;   //create a name for real time control loop flag
String command = "stop ";         //create a String object name for operator command string
String loopError = "no error";    //create a String for the real time control loop error system
unsigned long oldLoopTime = 0;    //create a name for past loop time in milliseconds
unsigned long newLoopTime = 0;    //create a name for new loop time in milliseconds
unsigned long cycleTime = 0;      //create a name for elapsed loop cycle time
const long controlLoopInterval = 1000; //create a name for control loop cycle time in milliseconds

//=========================================================================================
// Startup code to configure robot and pretest all robot functionality (to run once)
// and code to setup robot mission for launch.
//=========================================================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  boat.setPropSpeed(100);
}
//=============================================================================
// Flight code to run continuously until robot is powered down
//=============================================================================
void loop() {
  // Get operator input from serial monitor
  command = getOperatorInput();

  if (command == "stop") realTimeRunStop = false;     // skip real time inner loop
  else realTimeRunStop = true;                        // Set loop flag to run = true

  // real-time loop -------------------------------------------------------------
  while(realTimeRunStop == true) {        // if OCU-Stop not commanded, run control loop
    if (checkOperatorInput() == 1){
      break;
    }
    if (newLoopTime - oldLoopTime >= controlLoopInterval) { // if true run flight code
      oldLoopTime = newLoopTime;          // reset time stamp

      // SENSE-THINK-ACT =============================================================================
      // SENSE -------------------------------------------------------------
      /*
      boat.updatesensors()
      update irDataArray
      update pixyDataArray
      */
      // THINK -------------------------------------------------------------
      // processData(); // Uses data arrays to update irDecisionArray, pixyDecisionArray
      boat.state = commandState(); // Uses command to update boat state
      boat.stateController(); // Uses decision arrays and current state to update heading, velocity, state

      // ACT ---------------------------------------------------------------
      // boat.move(); // Uses heading and velocity to move boat

      // END SENSE-THINK-ACT =============================================================================

      // Check to see if all code ran successfully in one real-time increment
      if (checkCycleTime() == 1){
        break;
      }
    } // end flight code
  } // end real-time loop
} // end main loop

//========================================================================================
// Functions for flight code
//========================================================================================
// OPERATOR INPUT FUNCTIONS ------------------------------------------------------------------------------
String getOperatorInput()
{
  Serial.println(F("======================================================================================"));
  Serial.println(F("|Robot Behavior-Commands: chase(moves robot), stop(e-stops motors), idle(robot idles)|"));
  Serial.println(F("|                                                                                    |"));
  Serial.println(F("| Please type desired robot behavior in command line at top of this window           |"));
  Serial.println(F("| and then press SEND button.                                                        |"));
  Serial.println(F("======================================================================================"));
  while (Serial.available()==0) {};   // do nothing until operator input typed
  command = Serial.readString();      // read command string
  //command.trim();
  Serial.print(F("| New robot behavior command is: "));    // give command feedback to operator
  Serial.println(command);
  Serial.println(F("| Type 'stop' to stop control loop and wait for new command                          |"));
  Serial.println(F("======================================================================================"));
  return command;
}

int checkOperatorInput() {
  // Check if operator inputs a command during real-time loop execution
  if (Serial.available() > 0) {         // check to see if operator typed at OCU
    realTimeRunStop = false;            // if OCU input typed, stop control loop
    command = Serial.readString();      // read command string to clear buffer
    return 1;                              // break out of real-time loop
  }
  else {realTimeRunStop = true;}        // if no operator input, run real-time loop

  // Real-Time clock control. Check to see if one clock cycle has elapesed before running this control code
  newLoopTime = millis();               // get current Arduino time (50 days till wrap)
  return 0;
}

int checkCycleTime() {
  cycleTime = millis()-newLoopTime;     // calculate loop execution time
  if( cycleTime > controlLoopInterval){
    Serial.println("******************************************");
    Serial.println("error - real time has failed, stop robot!"); // loop took too long to run
    Serial.print(" 1000 ms real-time loop took = ");
    Serial.println(cycleTime);                                   // print loop time
    Serial.println("******************************************");
    return 1;          // break out of real-time inner loop
    }
  else {
    return 0;
  }
}

// STATE CONTROLLER FUNCTIONS ------------------------------------------------------------------------------

int commandState(){ // Takes command, returns int for state for switch
  if (command == "stop\n"){
    return 1;
  }
  else if (command == "idle\n"){
    return 2;
  }
  else if (command == "chase\n"){
    return 3;
  }
  else if (command == "search\n"){
    return 4;
  }
  else {
    Serial.println(command);
    return 0;
  }
}
