#include <Servo.h> 

Servo motor;
int pos = 0;
int motorPin = 9;
int buttonPin = 11;

void Sweep()
{
	Serial.print("WORKS");
    for (pos = 0; pos < 180; pos += 5)
    {
    motor.write(pos);
		delay(5);
    }

    delay(3000);

    for (pos = 180; pos > 0; pos -= 5) 
    {
      motor.write(pos);
			delay(5);
}

void setup() 
{
	pinMode(buttonPin,INPUT_PULLUP); 
	Serial.begin(9600); 
	motor.attach(motorPin);
	for (pos = 90; pos > 0; pos -= 10)
	{
		motor.write(pos);
		delay(5);
	}

}

void loop() 
{
	if (digitalRead(buttonPin) == LOW)
	{
    Sweep();
	}
}