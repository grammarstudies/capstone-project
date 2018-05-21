int speakerPin = 3;
int ledPin = 4;
bool reachedGround;
int siren[] = {}
void setup() 
{
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  if (reachedGround)
  {
    digitalWrite(ledPin,HIGH);
    
  }
}
