// Adapted Wire Master Reader (Nicholas Zambetti) 
// Use of the Wire library
// Reads two arrays of bytes from two separate slaves as an 
// I2C/TWI master device.
// Refer to the "Wire Slave Sender" example for use with this
// By Aaron Marks Nov. 2018

// To wire, all serial clock pins (A4) should be connected to eachother
// and all serial data pins should be connected (A5)

#include <Wire.h>

const unsigned int arrayLength1=10;
const unsigned int arrayLength2=6;
byte slave1[arrayLength1];
byte slave2[arrayLength2];

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {

  //First read from Slave 1
  Wire.requestFrom(7, arrayLength1);    // request 10 bytes from slave device #8
  
  while (Wire.available()) { // slave may send less than requested
    for(byte i=0; i<arrayLength1; i++){ //slave sends the array 1 byte at a time
      slave1[i] = Wire.read(); // receive a byte and add it to the array
    }
    Serial.print("[");
    for(byte i =0; i<arrayLength1; i++){
      Serial.print(slave1[i]);
    }
    Serial.println("]");
  }

  // Then read from slave 2
  Wire.requestFrom(8, arrayLength2);    // request 6 bytes from slave device #8
  
  while (Wire.available()) { // slave may send less than requested
    for(byte i=0; i<arrayLength2; i++){ //slave sends the array 1 byte at a time
      slave2[i] = Wire.read(); // receive a byte and add it to the array
    }
    Serial.print("[");
    for(byte i =0; i<arrayLength2; i++){
      Serial.print(slave2[i]);
    }
    Serial.println("]");
  }
  
  delay(500);
}
