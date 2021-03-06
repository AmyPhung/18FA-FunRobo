#ifndef Tugboat_h
#define Tugboat_h

#include <Servo.h>
#include "SenseTarget.h"

#define NUM_PTS 35

class Tugboat
{
  public:
    Tugboat();
    void init();
    void stateController();


    // Think variables - desired values
    float heading;  // Turn in degrees
    float velocity; // Between -1 and 1

    
    // Act variables
    float cmd_heading;  // Turn in degrees
    float cmd_velocity; // Between -1 and 1



    // To make private:
    // SENSE
    Pixy pixy;
    SenseTarget sensepixy;
    int pixyDataArray[NUM_PTS];
    void updatePixy();
    
    int irDataArray[NUM_PTS]; 

    // THINK
    int state;      // Integer representing state
    float irDecisionArray[NUM_PTS];
    float pixyDecisionArray[NUM_PTS];
    
    void arbiter();
    
    // ACT
    void setPropSpeed(int speedPercentage);
    void setHeading(int degHeading);
    Servo propellor;
    Servo rudder;
    int propellorPin = 6;
    int rudderPin = 3;
 

  
    // States
    void stop();
    void idle();
    void chase();
    void search();
    
  private:

};

#endif
