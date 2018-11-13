#define NUM_PTS 35

class Tugboat
{
public:
  // VARIABLES =================================================================
  // Sense variables
  int irDataArray[NUM_PTS];
  int pixyDataArray[NUM_PTS];

  // Think variables
  int state;      // Integer representing state
  float irDecisionArray[NUM_PTS];
  float pixyDecisionArray[NUM_PTS];

  // Act variables
  float heading;  // Turn in degrees
  float velocity; // Between -1 and 1

  // FUNCTIONS =================================================================
  // Sense Functions -----------------------------------------------------------


  // Think Functions -----------------------------------------------------------
  void stateController() {
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

  void stop() {

  }
  void idle() {

  }
  void chase() {

  }
  void search() {

  }
  /*
  void processData() { // Takes irDataArray, pixyDataArray as input. Modifies irDecisionArray, pixyDecisionArray
    return;
  }

  void arbiter() { // Takes irDecisionArray, pixyDecisionArray, state as input. Modifies heading, velocity, and state
    return;
  }
  */
  // Act Functions -------------------------------------------------------------
  // move(heading, velocity)
private:
};
