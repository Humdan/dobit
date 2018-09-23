/*  doBit_100          doBits Labs - Humdan Bakhshi
 *  version 1.0.0         11/18/2016
 *  Description:
 *  Arduino nano v3.0 with BLE HC-05 at 5v
 *  
 *  v100:  BLE Serial controller to push Towerpro SG90 Servo
 *  
 */

#include <Servo.h>

// Variable declarations__
int LED = 4; // LED DEBUG OBJECT
int servoPin = 3;  // servo pin PWM pin can be 3,5,6,9,10,11

int tapDelay = 1000; // tap delay
int shortDelay = tapDelay/4; // for double tapping
char input; // input from serial
Servo Servo1; // servo object

void setup() {
  pinMode(0, OUTPUT); // debug LED object
  Servo1.attach(servoPin); //attach servo object to pulse pin
  Serial.begin(9600);
  Servo1.write(0);// set initial servo condition to 0
  Serial.println("Ready");
}


void loop() {
/* startup > debug checks > usr calibrate > standBy
 *      |_____debug off________|
 */
  
 // servoCheck(); // SERVO CHECK LOOP
  standBy();
}// END LOOP


void standBy() {
  // functions after initial check has passed
  // takes a char and makes a move
  if (Serial.available() > 0) // enter function if serial com is open
  {
    input = Serial.read();
    if (input == '1')  {
      tapOn();
    }
    else if (input == '2')
    {
      tapOff();
    }
    else if (input == '3')
    {
      tap90();
    }
    else if (input == '4')  {
      tap180();
    }
    else
    {
      Serial.print("Standby");
      Serial.println(input);
    }  // close last else
  } // close ifSerial.available
} // END ready



void servoCheck() {
  // Make servo go to 0 degrees
  Servo1.write(0);
  delay(1000);
  // Make servo go to 90 degrees
  Servo1.write(90);
  delay(1000);
  // Make servo go to 180 degrees
  Servo1.write(180);
  delay(1000);
} // END servo check

void servoCal() {
  // calibrate the servo position
  // continue moving until a button is pressed
  // measure time interval in between pulses
  // update angle value somehow
}// END servoCal function


void debugCheck() {
  // this function uses serial input 1/0 to set the state of pin 3
  // functions after initial check has passed
  if (Serial.available() > 0) // enter function if serial com is open
  {
    input = Serial.read();
    if (input == '1')  {
      Serial.println("ON");
      digitalWrite(LED, HIGH);
      delay(2000);
    }
    else if (input == '0')
    { Serial.println("OFF");
      digitalWrite(LED, LOW);
      delay(2000);
    }
    else
    { Serial.println("NO INPUT");
      Serial.println(input);
    }  // End else statement
  } // END if(serial.available)
} // END debugCheck function

void tap180() {
  Serial.println("Full 180 Tap&Return");
  digitalWrite(LED, HIGH); // turn on debug LED
  Servo1.write(180);
  delay(tapDelay);
  Servo1.write(0);// move servo back to position
  digitalWrite(LED, LOW); // turn off debug LED
}// END tap180

void tapOn(){
  Serial.println("90Deg Tap ON");
  digitalWrite(LED, HIGH); // turn on debug LED
  Servo1.write(90);
  digitalWrite(LED, LOW); // turn off debug LED
} // close tapOn()

void tapOff(){
  Serial.println("90Deg Return OFF");
  digitalWrite(LED, HIGH); // turn on debug LED
  Servo1.write(0);
  digitalWrite(LED, LOW); // turn off debug LED
} // close tapOff()

void tap90() {
  Serial.println("90Deg Tap&Return");
  digitalWrite(LED, HIGH); // turn on debug LED
  Servo1.write(90);
  delay(tapDelay);
  Servo1.write(0);// move servo back to position
  digitalWrite(LED, LOW); // turn off debug LED
} // END tap90

void push180Dbl() { // push full double tap
  Serial.println("Doubletap FullPush");
  digitalWrite(LED, HIGH); // turn on debug LED
  Servo1.write(180);
  delay(shortDelay);
  Servo1.write(150);
  delay(shortDelay);
  Servo1.write(180);
  delay(shortDelay);
  Servo1.write(0);// move servo back to position
  digitalWrite(LED, LOW); // turn off debug LED
}// END push180dbl

void push90Dbl() { // push half double tap
  Serial.println("Doubletap HalfPush");
  digitalWrite(LED, HIGH); // turn on debug LED
  Servo1.write(90);
  delay(shortDelay);
  Servo1.write(60);
  delay(shortDelay);
  Servo1.write(90);
  delay(shortDelay);
  Servo1.write(0);// move servo back to position
  digitalWrite(LED, LOW); // turn off debug LED
}// END pushHalfDbl



