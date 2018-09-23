
#include <Servo.h> 

// Variable declarations__
int servoPin = 9;  // servo pin
 
Servo Servo1; // servo object


void setup() { 
   Servo1.attach(servoPin); //attach servo object to pulse pin
   Serial.begin(9600);
}


void loop(){ 
//servoCheck();
ready();
}


void ready(){
  // functions after initial check has passed
}

void servoCheck(){
     // Make servo go to 0 degrees 
   Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90); 
   delay(1000); 
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   delay(1000); 
} // end servo check
  
