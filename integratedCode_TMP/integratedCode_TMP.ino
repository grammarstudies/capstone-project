//we'll put all of the modules together in this tab
/* 
before flight, we'll have to (RESET MOTOR POSITION), (CALIBRATE ALTIMETER) or something
once altimeter reads correct height with enough certainty, either (INDICATE READY STATUS VIA LED) 
so that controller can activate with bluetooth or (AUTOMATICALLY INITIATE DESCENT (depends upon how the descent is being done))
once descent is initiated, (USE SWEEP FUNCTION) to press down on camera
once descent is completed, (REPEAT SWEEP FUNCTION OR SOMETHING) to turn camera off, then
(FLASH LED) and (ACTIVATE SPEAKERS) n stuff
probably include a button to (DEACTIVATE ALARM SYSTEM)
*/
#include <Servo.h> //servo library to access functions

/*VARIABLES*/
Servo motor;
int pos = 0;
int motorPin = 9;
int buttonPin = 11;
int trigPin = 12;
int echoPin = 13;
long duration; //in microseconds
long distance; //in centimeters

/*FUNCTIONS*/
void Sweep()
{
	Serial.print("WORKS");
    for (pos = 0; pos < 180; pos += 5) //sweep to one side
    {
    motor.write(pos);
		delay(5);
    }

    delay(3000); //hold down for 3 seconds

    for (pos = 180; pos > 0; pos -= 5) //sweep back
    {
      motor.write(pos);
			delay(5);
    }
}
void SearchForGround()
{
	// Clears the trigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);
// Calculating the distance
	distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
	Serial.print("Distance: ");
	Serial.println(distance);
}



void setup() 
{
	pinMode(buttonPin,INPUT_PULLUP); //has the arduino listen for data from the button
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	Serial.begin(9600); //initializes serial monitor; effectively serves as the console; transmitting data at 9600 bits/sec
	motor.attach(motorPin);
	for (pos = 90; pos > 0; pos -= 10) //resets motor to default position
	{
		motor.write(pos);
		delay(5);
	}

}

void loop() 
{
	SearchForGround();
	if (digitalRead(buttonPin) == LOW)
{
	Sweep();
}
}