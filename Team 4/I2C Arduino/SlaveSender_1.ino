// Adapted Wire Slave Sender 1 (Nicholas Zambetti) 
// Use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this
// By Aaron Marks Nov. 2018


#include <Wire.h>

void setup() {
  Wire.begin(7);                // join i2c bus with address #7
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  byte myArray[] = {0,1,2,3,4,5,6,7,8,9};//byte array is much simpler to implement than int array but is unsigned and 0-255
  Wire.write(myArray,10); // respond with message of 10 bytes - must declare length of array here
  // as expected by master
}
