/*
 * Author: Anirudh Acharya
 * W/ other sources
 * DC Motor driver + Ultrasound
  HC-SR04 Ping distance sensor
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

const int LEFT_MOTOR_DIR_PIN = 7;
const int LEFT_MOTOR_PWM_PIN = 9;
const int RIGHT_MOTOR_DIR_PIN = 8;
const int RIGHT_MOTOR_PWM_PIN = 10;
const int TRIG_PIN = 2;
const int ECHO_PIN = 3;
const int LED = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode( LEFT_MOTOR_DIR_PIN, OUTPUT );
  pinMode( LEFT_MOTOR_PWM_PIN, OUTPUT );
  pinMode( RIGHT_MOTOR_DIR_PIN, OUTPUT );
  pinMode( RIGHT_MOTOR_PWM_PIN, OUTPUT );
  pinMode( TRIG_PIN, OUTPUT);
  pinMode( ECHO_PIN, INPUT);
  pinMode( LED, OUTPUT);
  Serial.begin( 57600 );
}

void loop() {

  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
   
  // put your main code here, to run repeatedly:
  digitalWrite( LEFT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_PWM_PIN, HIGH );
  digitalWrite( LEFT_MOTOR_PWM_PIN, HIGH );
  delay(100);      
  digitalWrite( RIGHT_MOTOR_PWM_PIN, LOW );
  digitalWrite( LEFT_MOTOR_PWM_PIN, LOW );
}

void stop() {
}

void forward() {
}

void left_turn() {
}

void right_turn() {
}

void back() {
}
}

