/*
 * Author: Anirudh Acharya
 * w/ other sources
 * DC Motor driver + Ultrasound collision detection

  HC-SR04 Ping distance sensor - Ultrasound
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
  Red POS to Arduino pin 11
  Green POS to Arduino pin 10
  560 ohm resistor to both LED NEG and GRD power rail
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define LEFT_MOTOR_DIR_PIN (7)
#define LEFT_MOTOR_PWM_PIN (9)
#define RIGHT_MOTOR_DIR_PIN (8)
#define RIGHT_MOTOR_PWM_PIN (10)
#define TRIG_PIN (2)
#define ECHO_PIN (3)
#define LED (13) //pin
#define DUTY_CYCLE (65)
#define COLLISION_DISTANCE (15)
#define OUT_OF_RANGE_DISTANCE (200)
#define TURN_DELAY (2000)
#define STOP_DELAY (750)
#define TURN_DUTY_CYCLE (100)
#define ECHO_SAMPLE_DELAY (200)
#define REVERSE_DELAY (2000)
#define STUCK_THRESHOLD (4) // 4 = 360 degrees
#define LED_BLINK_DELAY (10) // in ms
#define TIME_SINCE_LAST_COLLISION_THRESHOLD (10000) // in ms

int stuck;
int timeSinceCollision;

void setup() {
  // put your setup code here, to run once:
  pinMode( LEFT_MOTOR_DIR_PIN, OUTPUT );
  pinMode( LEFT_MOTOR_PWM_PIN, OUTPUT );
  pinMode( RIGHT_MOTOR_DIR_PIN, OUTPUT );
  pinMode( RIGHT_MOTOR_PWM_PIN, OUTPUT );
  pinMode( TRIG_PIN, OUTPUT);
  pinMode( ECHO_PIN, INPUT);
  pinMode( LED, OUTPUT);
  Serial.begin( 9600 );
  ledBlink(3);
  stuck = 0;
  timeSinceCollision = 0;
}

void loop() {

  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); //send ping
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH); // read ping
  distance = (duration/2) / 29.1;

  if (distance >= OUT_OF_RANGE_DISTANCE ){
    Serial.println("Out of range");
    digitalWrite (LED, LOW);
    forward();
    stuck = 0;
  }
  else if (distance <= 0) { // should not happen
    Serial.println("Illegal distance (<=0)");
    ledBlink(5);
    stop();
    back(REVERSE_DELAY);
    stop();
    right_turn();
    stuck = 0;
  }
  else {
    Serial.print(distance);
    Serial.print(" cm");
    if (distance <= COLLISION_DISTANCE) {
      Serial.println(", Collision detected! Turning...");
      digitalWrite(LED, HIGH);
      stuck++;
      stop();
      right_turn();

      /*
      timeSinceCollision = micros(); //record time of collision
      if (timeSinceCollision >= TIME_SINCE_LAST_COLLISION_THRESHOLD) {
          left_turn();
          timeSinceCollision = 0;
      }
      else {
          right_turn();
      }
      */

      // if stuck for long, reverse and change direction
      if (STUCK_THRESHOLD == stuck) {
        ledBlink(3);
        Serial.println("Stuck! Reversing and turning...");
        stop();
        back(REVERSE_DELAY);
        stop();
        left_turn();
        stuck = 0;
      }
    }
    else {
      Serial.println("");
      digitalWrite (LED, LOW);
      forward();
      stuck = 0;
    }
  }

  delay(ECHO_SAMPLE_DELAY);      
}

void stop() {
  digitalWrite( LEFT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_PWM_PIN, LOW );
  digitalWrite( LEFT_MOTOR_PWM_PIN, LOW );
  delay(STOP_DELAY);
}

void forward() {
  digitalWrite( LEFT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_DIR_PIN, HIGH );

  digitalWriteDutyCycle (LEFT_MOTOR_PWM_PIN, DUTY_CYCLE);
  digitalWriteDutyCycle (RIGHT_MOTOR_PWM_PIN, DUTY_CYCLE);
}

void left_turn() {
  digitalWrite( LEFT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_PWM_PIN, LOW );

  digitalWriteDutyCycle (LEFT_MOTOR_PWM_PIN, TURN_DUTY_CYCLE);
  delay(TURN_DELAY);
}

void right_turn() {
  digitalWrite( LEFT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( RIGHT_MOTOR_DIR_PIN, HIGH );
  digitalWrite( LEFT_MOTOR_PWM_PIN, LOW );
  
  digitalWriteDutyCycle (RIGHT_MOTOR_PWM_PIN, TURN_DUTY_CYCLE);
  delay(TURN_DELAY);
}

void back(int reverseDelay) {
  digitalWrite( LEFT_MOTOR_DIR_PIN, LOW );
  digitalWrite( RIGHT_MOTOR_DIR_PIN, LOW );

  digitalWriteDutyCycle (RIGHT_MOTOR_PWM_PIN, DUTY_CYCLE);
  digitalWriteDutyCycle (LEFT_MOTOR_PWM_PIN, DUTY_CYCLE);

  //reverse for specified duration
  if (0 != reverseDelay) {
    delay(reverseDelay);
  }
}

void digitalWriteDutyCycle(int pin, int duty_cycle) { //only int duty cycle for now

  analogWrite(pin, duty_cycle);

  /*
  // custom PWM implementation
  int pwm_time_us = 1000;
  int on_in_us = (duty_cycle*pwm_time_us/100);
  int off_in_us = pwm_time_us - on_in_us;

  digitalWrite( pin, HIGH);
  delayMicroseconds(on_in_us);
  digitalWrite (pin, LOW);
  delayMicroseconds(off_in_us); 
  */
}

void ledBlink(int times) {
  for (int i = 0; i<times; i++){
    digitalWrite( LED, HIGH );
    delay(LED_BLINK_DELAY);
    digitalWrite( LED, LOW );
  }
}

