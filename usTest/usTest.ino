/*
 * Author: Anirudh Acharya
 * w/ other sources
  HC-SR04 Ping distance sensor
  
  Distance calculated is mostly accurate
  
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 2
#define echoPin 3
#define led 13
//#define led2 10

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  /*
   * Explanation: The approximate speed of sound in dry air is given by the formula:
   *  Approx. speed of sound in dry air, c = 331.5 + 0.6 * [Air Temp. in Deg. C]
   *  At 20°C, c = 331.5 + 0.6 * 20 = 343.5 m/s
   *  c = 343.5 * 100 / 1000000 = 0.03435 cm/us (in cm per us)
   *  Distance = (t/2) * c [t = total time to and fro, t/2 = one way]
   * 
   *  Can also use "Pace of Sound".
   *  Pace of Sound = 1 / Speed of Sound = 1 / 0.03435 = 29.1 us/cm
   *  Distance = (t/2) / 29.1
   */
 

  if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    //digitalWrite(led2,LOW);
  }
  else {
    digitalWrite(led,LOW);
    //digitalWrite(led2,HIGH);
  }
  
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

