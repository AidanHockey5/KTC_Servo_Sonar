#include <Servo.h>
unsigned int samples[180];
int echo = 12;
int trig = 13;
Servo s;

void setup() 
{
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  s.attach(9);
  s.write(0);
  Serial.begin(115200);
}

void loop() 
{
  for(int i = 0; i<180; i++)
  {
    s.write(i);
    unsigned int d = Distance();
    samples[i] = d;
    Serial.println(d);
    delay(5);
  }
  int lowest = GetLowest(samples, 180);
  if(lowest == -1)
    s.write(0);
  else
    s.write(lowest);
  delay(5000);
  s.write(0);
  delay(1000);
}

int GetLowest(unsigned int arr[], int count)
{
  int tmp = 10000;
  int lowestPoint = 0;
  for(int i = 0; i<count; i++)
  {
    if(arr[i] < tmp)
    {
      lowestPoint = i;
      tmp = arr[i];
    }
  }
  Serial.print("LOWEST DEGREE: "); Serial.println(lowestPoint);
  if(lowestPoint == 9999)
    return -1;
  else
    return lowestPoint;
}

unsigned int Distance()
{
  digitalWrite(echo, LOW);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  unsigned long echoValue = pulseIn(echo, HIGH);
  if(echoValue == 0)
    return 9999;
  unsigned int d = echoValue / 58.138;
  return d;
}
