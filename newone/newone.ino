#include <Servo.h>
const int trigPin = 8;
const int echoPin = 9;
#define alarm 10

int range = 5;//range in inches
// defining time and distance
long duration;
int distance;
Servo myServo; // Object servo
void setup() {
  pinMode(trigPin, OUTPUT); // trigPin as an Output
  pinMode(echoPin, INPUT); // echoPin as an Input
  Serial.begin(9600);
  myServo.attach(11); // Pin Connected To Servo
}
void loop() {

  // rotating servo i++ depicts increment of one degree
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  
  Serial.print(i); 
  Serial.print(","); 
  Serial.print(distance); 
  Serial.print(".");
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}


int calculateDistance(){ 
 // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // Take reading on echo pin
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if(inches < 5) {
    Serial.println("DANGER");
 
    tone(alarm, 2000); 
    delay(100);
  }
  else 
  {
    Serial.println("GOOD");
   
     noTone(alarm);
     delay(100);
  }  
  
  delay(200);
}

long microsecondsToInches(long microseconds)
{

  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{

  return microseconds / 29 / 2;
  distance= duration*0.034/2;
  return distance;
}
