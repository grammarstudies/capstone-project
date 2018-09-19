//Basic sensor capabilities derived from https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
const int trigPin = 5;
const int echoPin = 6;
int prevPulse = 400;
int newPulse = 400;
int average, counter, lastRejected;
int credence = 0;
long duration, distance;
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
}
