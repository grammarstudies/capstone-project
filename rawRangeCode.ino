//Basic sensor capabilities derived from https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
const int trigPin = 5;
const int echoPin = 6;
long duration;
long distance;

void setup()
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	Serial.begin(9600);
}
void loop()
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	duration = pulseIn(echoPin, HIGH);
	distance= duration*0.034/2;
	Serial.println(distance);
}
