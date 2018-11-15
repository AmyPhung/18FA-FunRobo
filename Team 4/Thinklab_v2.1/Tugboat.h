#ifndef Tugboat_h
#define Tugboat_h

#include <Servo.h>

#define NUM_PTS 35

//Servo propellor;
//int propellorPin = 6;

class Tugboat
{
  public:
    Tugboat();
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

    void setPropSpeed(int speedPercentage);
  
  private:
    Servo propellor;
    int propellorPin = 6;

    
    // States
    void stop();
    void idle();
    void chase();
    void search();
};

#endif
