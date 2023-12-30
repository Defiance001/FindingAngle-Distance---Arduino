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

int Led1 = 8; 
int Led2 = 9;

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
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  servo1.attach(7);
  servo1.write(0);
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
  float Distance = duration*0.034/2;

  if (currentTime - searchTargetST >= searchTargetInterval){
    int CservoAngle = servo1.read();
    if(Distance<100 && CservoAngle>0){
      int targetAngle = servo1.read();
      float targetDistance = Distance; 
      if(currentTime - x >= y){
        x = currentTime;
        Serial.print(targetAngle);
        Serial.print(" , ");
        Serial.println(targetDistance);
        }
       Serial.print(targetAngle);
       Serial.print(",");
       Serial.println(targetDistance);
      }
    }
  
  if (currentTime - startTimeServo >= servoInterval){
    startTimeServo = currentTime; 
    servo1.write(servoAngle);
    servoAngle++;
    if(servoAngle == 160) servoAngle = 20;
    }
}


