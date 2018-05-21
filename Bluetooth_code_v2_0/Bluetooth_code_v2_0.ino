//Jesse DeWald 
//November 18, 2014
//The University of Texas at Austin
//UTeachEngineering - Engineer Your World
//This code is available in the Public Domain

//v2.0
//Updated null overwrite sequence, added buffer overload protection, test for position before launch/reset
//broke definitions and functions into header files
//interrupt function now only toggles a button flag 
//toggleServo handles all servo functionality
//setup functions added to increase readability
//commented func and var files appropriately. 

/*---------------------------------------------------------Bluetooth Release Mechanism------------------------------------------------------------*/


//*These files must be included for functionality*
#include "Arduino.h"
#include <Servo.h>
#include "Bluetooth_vars.h"
#include "Bluetooth_func.h"
#include <Wire.h>

//These commands run only once
void setup() 
{ 
  startBT();            //use this to start bluetooth with default settings
  //startBT(2,3)        //you can also specify the Button-Pin and the Servo-Pin, respectively
  setServo();           //use this to set the servo with default settings
  //setServo(10, 150, 3) //you can also specify the Loading and Launching Positions (in degrees), and Countdown Length (in seconds). Respectively.
  Wire.begin();
} 
 
//These commands will loop forever
void loop()
{
  if (Serial.available())   //have you sent a command from the Bluetooth Terminal?
  {
    processCommand();       //if you have, process that command.
  }
  if (buttonPressed)        //have you pressed the button?
  {
    toggleServo();          //if you have, toggle the servo
  }
}

