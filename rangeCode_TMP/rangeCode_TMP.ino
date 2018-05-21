const int trigPin = 5;
const int echoPin = 6;
int prevPulse = 400;
int newPulse = 400;
long duration;
long distance;
int garbage[] = {2568,2331,9065,3,45,45,24,3242,342,4,264,3,6543,42,2,12,12,12,23,34,56,76,55,1000,401,401,433,333,256,390,101,44,5,5};

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
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  /*for (int x : garbage)
  {
    if ((x - prevPulse < 100) && (x - prevPulse > -100) && (x < 400))
    {
      newPulse = x;
      Serial.print("ACCEPTED "); Serial.println(newPulse);
    }
    else 
    {
      Serial.print("RETAINED"); Serial.print(newPulse); Serial.print(", REJECTED"); Serial.println(x);
    }
    prevPulse = newPulse;
  }*/
}
void loop()
{
  if (/*((avgPulse() - prevPulse) < 100) && ((avgPulse() - prevPulse) > -100) &&*/ avgPulse() < 400)
  {
    newPulse = avgPulse();
    Serial.print("ACCEPTED");
  	Serial.println(avgPulse());
  }
  else 
	{
		Serial.print("REJECTED"); 
		Serial.println(avgPulse());
	}
  prevPulse = newPulse;
}