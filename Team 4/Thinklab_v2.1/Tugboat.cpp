

Tugboat::Tugboat()
{
  Serial.println("New boat setup!")
  asdf
  propellor.attach(propellorPin);
}

// FUNCTIONS =================================================================
// Sense Functions -----------------------------------------------------------


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

}
void Tugboat::idle() {

}
void Tugboat::chase() {

}
void Tugboat::search() {

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
/*
//function to set propellor speed by percentage
void setPropSpeed(int speedPercentage){
  int microSec;
  if (speedPercentage>99){          //2000 mm [this is a stand in number]
    microSec= 2000;       //full speed forward
  }
  else if (speedPercentage<=99 && speedPercentage>=0){   //1000 [stand in]
    microSec = map(speedPercentage,0, 100, 1500, 2000); // test speeds of different distances
  }
  else if (speedPercentage < 0){
    microSec=1000;         //back up slowly from narwhale to prevent running it over
  }
  propellor.writeMicroseconds(microSec);
}
*/
// move(heading, velocity)
private:
//Servo propellor;

//int propellorPin = 6;
};
