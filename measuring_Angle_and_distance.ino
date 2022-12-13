#include <Servo.h>
Servo servo1; 

int servoAngle = 0;
const int trigPin = 6;
const int echoPin = 5; 
long duration; 
float presentDistance;
float previousDistance;
unsigned long startTime = 0;
unsigned long timeInterval = 1000;

unsigned long startTimeServo = 0; 
unsigned long servoInterval = 20;

unsigned long sonicStartTime = 0;
unsigned long sonicIntervalOne = 0.002; 
unsigned long sonicIntervalTwo = 0.01; 

unsigned long searchTargetST = 0;
unsigned long searchTargetInterval = 1000;

unsigned long x = 0;
unsigned long y = 1000; 

int averageEnviromentDistance; 

int calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration*0.034/2;
  }

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  servo1.attach(7);
  servo1.write(0);
  //Serial.println("calibrating....");
  int distance1 = calculateDistance();
  delay(2000);
  servo1.write(32);
  int distance2 = calculateDistance();
  delay(2000);
  servo1.write(64);
  int distance3 = calculateDistance();
  delay(2000);
  servo1.write(96); 
  int distance4 = calculateDistance();
  delay(2000);
  servo1.write(128);
  int distance5 = calculateDistance();
  delay(2000);
  servo1.write(160);
  int distance6 = calculateDistance();
  averageEnviromentDistance = ((distance1 + distance2 + distance3 + distance4 + distance5 + distance6)/6) - 10;
}

void loop(){
  unsigned currentTime = millis(); 

  digitalWrite(trigPin, LOW);
  
  if (currentTime - sonicStartTime >= sonicIntervalOne){
    sonicStartTime = currentTime;
    digitalWrite(trigPin, HIGH); 
    }
  if (currentTime - sonicStartTime >= sonicIntervalTwo){
    sonicStartTime = currentTime;
    digitalWrite(trigPin, LOW); 
    }
  duration = pulseIn(echoPin, HIGH);
  int Distance = duration*0.034/2;

  if (currentTime - searchTargetST >= searchTargetInterval){
    int CservoAngle = servo1.read();
    if(Distance<50 && CservoAngle>30){
      int targetAngle = servo1.read();
      int targetDistance = Distance; 
      if(currentTime - x >= y){
        x = currentTime;
        Serial.print(targetAngle);
        Serial.print(" , ");
        Serial.println(targetDistance);
        }
       //Serial.print(targetAngle);
       //Serial.print(" , ");
       //Serial.println(targetDistance);
      }
    }
  
  if (currentTime - startTimeServo >= servoInterval){
    startTimeServo = currentTime; 
    servo1.write(servoAngle);
    servoAngle++;
    if(servoAngle == 160) servoAngle = 20; 
    }
}



