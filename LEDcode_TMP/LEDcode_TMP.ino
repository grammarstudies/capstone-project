#include <Servo.h>

Servo motor;
int pos = 0;

void setup() {
pinMode(11,INPUT_PULLUP);
Serial.begin(9600);
motor.attach(9);
}

void loop() 
{
  if (digitalRead(11) == LOW)
  {
    Serial.print("WORKS");
    for (pos = 0; pos < 180; pos+= 2)
    {
    motor.write(pos);
    }
    motor.write(175);
    delay(3000);
    for (pos = 180; pos > 0; pos -= 2)
    {
      motor.write(pos);
    }
    motor.write(5);
  }
}