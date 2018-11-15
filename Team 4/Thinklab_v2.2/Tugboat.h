#ifndef Tugboat_h
#define Tugboat_h

#include <Servo.h>

#define NUM_PTS 35

class Tugboat
{
  public:
    Tugboat();
    void init();
    void stateController();

    int irDataArray[NUM_PTS];
    int pixyDataArray[NUM_PTS];

    // Think variables
    int state;      // Integer representing state
    float irDecisionArray[NUM_PTS];
    float pixyDecisionArray[NUM_PTS];

    // Act variables
    float heading;  // Turn in degrees
    float velocity; // Between -1 and 1



    // To make private:
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
