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
const int motorPin = 9;
const int buttonPin = 11;
const int trigPin = 5;
const int echoPin = 6;
int prevPulse = 400;
int newPulse = 400;
int average, counter, lastRejected;
int credence = 0;
int pos = 0; //in degrees
long duration; //in microseconds
long distance; //in centimeters

/*FUNCTIONS*/
int pulse()
{
  delay(100);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  return distance;
}
int avgPulse()
{
  int firstPulse = pulse();
  int secondPulse = pulse();
  int thirdPulse = pulse();
  int result = (firstPulse + secondPulse + thirdPulse) / 3;
  return result;
}
void Sweep(int angle, int wait)
{
	Serial.print("WORKS");
    for (pos = 0; pos < angle; pos += 5) //sweep to one side
    {
    motor.write(pos);
		delay(5);
    }

    delay(wait); //hold down for 3 seconds

    for (pos = angle; pos > 0; pos -= 5) //sweep back
    {
      motor.write(pos);
			delay(5);
    }
}
int SearchForGround()
{
	average = avgPulse();
  if (((average - prevPulse) < 100) && ((average - prevPulse) > -100)) //ACCEPTANCE
  {
    newPulse = average;
    Serial.println("SUCCESS");
  }
  else //REJECTION
  {
    Serial.print("FAILURE ");
    if (credence == 0)
    {
      lastRejected = average;
      credence++;
      Serial.println("1");
    }
    else if (credence == 3)
    {
      newPulse = average;
      lastRejected = -1000;
      credence = 0;
      Serial.println("2");
    }
    else //IF CREDENCE IS BETWEEN 0 AND 4
    {
      if (((average - lastRejected) < 100) && ((average - lastRejected) > -100))
      {
        lastRejected = average;
        credence++;
        Serial.println("3");
      }
      else
      {
        lastRejected = -1000;//cannot be null so an impossible number is in its place
        credence = 0;
        Serial.println("4");
      }
    }
  }
    Serial.print("REJECTED: "); Serial.print(lastRejected); Serial.print(", ACCEPTED: "); Serial.println(newPulse);
    Serial.print("AVERAGE: "); Serial.print(average); Serial.print(", CREDENCE: "); Serial.println(credence);
  prevPulse = newPulse;
	return newPulse;
}


/*RUNTIME FUNCTIONS*/
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
	if (digitalRead(buttonPin) == LOW) //INITIATE SEQUENCE
	{
		Sweep(180, 3000); //TURN CAMERA ON
		Sweep(180,100); //TURN VIDEO ON
		while (SearchForGround() > 5)
		{
		}
		Sweep(180,100); //TURN VIDEO OFF
		Sweep(180,5000); //TURN CAMERA OFF
	}
}