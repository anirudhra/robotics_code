  /*
   * MeArm with Ultrasound sensor
   * Author: Anirudh Acharya
   * 
   *  Distance Explanation: The approximate speed of sound in dry air is given by the formula:
   *  Approx. speed of sound in dry air, c = 331.5 + 0.6 * [Air Temp. in Deg. C]
   *  At 20°C, c = 331.5 + 0.6 * 20 = 343.5 m/s
   *  c = 343.5 * 100 / 1000000 = 0.03435 cm/us (in cm per us)
   *  Distance = (t/2) * c [t = total time to and fro, t/2 = one way]
   * 
   *  Can also use "Pace of Sound".
   *  Pace of Sound = 1 / Speed of Sound = 1 / 0.03435 = 29.1 us/cm
   *  Distance = (t/2) / 29.1
   */


#include <Servo.h> 
 
Servo BaseServo;  // create servo object to control a servo 
Servo RightServo;
Servo LeftServo;
Servo ClawServo;

int pos = 0;    // variable to store the servo position 
const int BaseServoPin = 4; 
const int RightServoPin = 5;
const int LeftServoPin = 6;
const int ClawServoPin = 11;
const int LedPin = 13;
const int ServoStep = 1;
const int trigPin = 2;
const int echoPin = 3;
const int delayTime = 300; // sampling delay ms
const int angle_closed = 105;
const int angle_open = 80;
const int delayStep = 10;

void setup() 
{ 
  Serial.begin (9600);
  pinMode(LedPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  BaseServo.attach(BaseServoPin);  // attaches the servo on pin 9 to the servo object 
  RightServo.attach(RightServoPin);  // attaches the servo on pin 9 to the servo object 
  LeftServo.attach(LeftServoPin);  // attaches the servo on pin 9 to the servo object 
  ClawServo.attach(ClawServoPin);  // attaches the servo on pin 9 to the servo object 
  ClawServo.write(180);
} 
 
 
void loop() 
{ 

  long duration, distance;
  
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 
  if (distance <= 7) {  // This is where the LED On/Off happens
    digitalWrite(LedPin, HIGH); // When the Red condition is met, the Green LED should turn off

    for (pos=angle_open; pos<=angle_closed; pos++) {
      LeftServo.write(pos);
      RightServo.write(pos);
      BaseServo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(delayStep);
    }

    ClawServo.write(90);
    Serial.println("Claw Closed:");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else if (distance <= 180 && distance >7) {
    digitalWrite(LedPin, LOW);
    for (pos=angle_closed; pos>=angle_open; pos--) {
      LeftServo.write(pos);
      RightServo.write(pos);
      BaseServo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(delayStep);
    }
    ClawServo.write(0);
    Serial.println("Claw Open:");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else {
    digitalWrite(LedPin, LOW);
    delay(delayStep);
    digitalWrite(LedPin, HIGH);
    delay(delayStep);
    digitalWrite(LedPin, LOW);
    Serial.println("Out of range");
  }
  
  delay(delayStep*5);
} 

