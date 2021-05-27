//Remote Agriculture Solution
// Autonomous Agro Bot
/*          Arduino based bot for automatic movement around the farm
  Dev: Aaryan Arora
  For Design For A Cause 2021
*/
//Libraries
#include <Servo.h>
int TurnDelay = 1100;
#define TRIGGER_PIN1  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
long duration, cm;

//Constants
const int motorA1 = 6;    //motor A positive (+) pin to pin 6 (PWM) (from L293D module!)
const int motorA2 = 9;        //motor A negative (-) pin to pin 9 (PWM)
const int motorB1 = 10;   //motor B positive (+) pin to pin 10 (PWM)
const int motorB2 = 11;   //motor B negative (-) pin to pin 11 (PWM)
Servo myservo;          //Create Servo object to control a servo

//Variables
int distance;         //Variable to store distance from an object
int checkRight;       //To store right distance
int checkLeft;        //To store left distance
int pos = 90;         //Variable to store the servo position. By default at 90 degrees the sensor will 'look' forward

//declaring functions
void forward();
void backward();
void stop();
void left();
void right();
int ultraFront();

void setup()
{
  myservo.attach(5);      //Servo pin connected to pin 5
  myservo.write(pos);     // tell servo to go to position in variable 'pos'
  //Setting Motor control pins to output
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  //Setting pins from Ultrasonic Sensor
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
}

void loop()
{

  //Read distance...
  distance = ultraFront();
  //Check for objects...
  if (distance > 15) {
    forward(); //All clear, move forward!
  }
  else if (distance <= 15) {
    stop(); //Object detected! Stop the robot and check left and right for the better way out!
    //Start scanning...
    for (pos = 0; pos < 180; pos += 1) { //goes from 0 degrees to 180 degrees
      myservo.write(pos);             //tell servo to go to position in variable 'pos'
      delay(10);                      //waits 10ms for the servo to reach the position
    }
    checkLeft = ultraFront();
    for (pos = 180; pos >= 0; pos -= 1) { //goes from 180 degrees to 0 degrees
      myservo.write(pos);             //tell servo to go to position in variable 'pos'
      delay(10);                      //waits 10ms for the servo to reach the position
    }
    checkRight = ultraFront();
    myservo.write(90);                   // Sensor "look" forward again
    //Finally, take the right decision, turn left or right?
    if (checkLeft <= 10 && checkRight <= 10) {
      backward(); //The route is closed... go back and then left(you can change to right as well depending on your choice and setup)
      delay(TurnDelay);
      left();
    }
    else if (checkLeft < checkRight) {
      right();
      delay(TurnDelay); // delay, change value if necessary to make robot turn.
    }
    else if (checkLeft > checkRight) {
      left();
      delay(TurnDelay); // delay, change value if necessary to make robot turn.
    }
  }
}

// functions for various type of motions
void forward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}
void backward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}
void right() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}
void left() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stop() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

//for measuring distance using ultrasonic sensor
int ultraFront() {
  
  digitalWrite(TRIGGER_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO_PIN1, INPUT);
  duration = pulseIn(ECHO_PIN1, HIGH);
  
  // Convert the time into a distance
  cm = (duration / 2) / 0.034;   // Multiply by 0.034 
  return cm;
}
