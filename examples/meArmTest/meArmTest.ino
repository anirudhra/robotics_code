// Sweep
// by BARRAGAN <http://barraganstudio.com> 

#include <Servo.h> 
 
Servo BaseServo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo RightServo;
Servo LeftServo;
 
int pos = 0;    // variable to store the servo position 

const int BaseServoPin = 4; 
const int RightServoPin = 3;
const int LeftServoPin = 2;
const int LedPin = 13;
const int delayTime = 10;
const int ServoStep = 1;

void setup() 
{ 
  BaseServo.attach(BaseServoPin);  // attaches the servo on pin 9 to the servo object 
  RightServo.attach(RightServoPin);  // attaches the servo on pin 9 to the servo object 
  LeftServo.attach(LeftServoPin);  // attaches the servo on pin 9 to the servo object 
  pinMode(LedPin, OUTPUT);
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += ServoStep)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    BaseServo.write(pos);              // tell servo to go to position in variable 'pos' 
    if (pos%45 == 0) {
      LeftServo.write(65);
      RightServo.write(65);
      digitalWrite(LedPin, LOW);           // turn the LED on (HIGH is the voltage level)  } 
      delay(delayTime);                      // waits 150ms for the servo to reach the position 
    }
    digitalWrite(LedPin, HIGH);          // turn the LED on (HIGH is the voltage level)
    delay(delayTime);                      // waits 150ms for the servo to reach the position 
  } 
  for(pos = 180; pos >= 1; pos -= ServoStep)     // goes from 180 degrees to 0 degrees 
  {                                
    BaseServo.write(pos);              // tell servo to go to position in variable 'pos' 
    if (pos%45 == 0) {
      LeftServo.write(90);
      RightServo.write(90);
      digitalWrite(LedPin, LOW);           // turn the LED on (HIGH is the voltage level)  } 
      delay(delayTime);                      // waits 150ms for the servo to reach the position 
    }
    digitalWrite(LedPin, HIGH);          // turn the LED on (HIGH is the voltage level)
    delay(delayTime);                      // waits 150ms for the servo to reach the position 
  }
} 

