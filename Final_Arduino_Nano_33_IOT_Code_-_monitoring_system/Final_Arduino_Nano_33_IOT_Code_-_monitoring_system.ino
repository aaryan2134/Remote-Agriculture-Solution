//Remote Agriculture Solution
//Monitoring System
/*          Using Arduino Nano 33 IOT to monitor farm conditions using IOT
  Dev: Aaryan Arora
  For Design For A Cause 2021
*/

//libraries
#define BLYNK_PRINT SerialUSB
#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#include <EduIntro.h>
/* Used this library for getting temperature reading from DHT 11
  Can be downloaded from here or arduino library manager
  https://github.com/arduino/EduIntro
*/

//for water level
#define TRIGGER_PIN1  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     12  // Arduino pin tied to echo pin on the ultrasonic sensor.

//for pesticide level
#define TRIGGER_PIN2  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     10  // Arduino pin tied to echo pin on the ultrasonic sensor.


//water pump
const int motorA1 = 2;    //motor A positive  pin to pin 6 (PWM) (from L293D module!)
const int motorA2 = 3;        //motor A negative  pin to pin 9 (PWM)


//pesticide pump
const int motorB1 = 5;   //motor B positive  pin to pin 10 (PWM)
const int motorB2 = 6;   //motor B negative  pin to pin 11 (PWM)


DHT11 dht11(D7);  // creating the object sensor on pin 'D7'
int water_level(); //to measure level of water in container
int pesticide_level(); //to measure level of pesticide in container


//Use your authorization token after creating new project in Blynk App
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";


//constants
int LDRpin = A0; // select the input pin for LDR
int LDRvalue = 0; // variable to store the value coming from the LDR
int lux = 0;         //to store the intensity of light in lux
long duration, cm;
int soil_pin = A2; //soil sensor pin
int moisture_value ; //storing result from soil sensor

BlynkTimer timer;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void myTimerEvent()
{
  //starting the DHT 11 sensor
  dht11.update();

  //Getting the LDR analog value
  LDRvalue = analogRead(LDRpin);
  //Using the formula for conversion from analog value to lux
  lux = (512000 / LDRvalue) - 500;

  //calculating moisture percentage using analog value of the sensor
  moisture_value = analogRead(soil_pin);
  //converting to percentage
  moisture_value = (moisture_value * 100) / 1023;
  //using formula to account for resistance
  moisture_value = 35 + (100 - moisture_value);

  //sending all values to the Blynk App using Virtual Pins
  Blynk.virtualWrite(V5, lux);
  Blynk.virtualWrite(V6, dht11.readCelsius());
  Blynk.virtualWrite(V7, dht11.readHumidity());
  Blynk.virtualWrite(V8, moisture_value);
  Blynk.virtualWrite(V0, water_level());
  Blynk.virtualWrite(V1, pesticide_level());

}
void setup() {
  //Setting pins from Ultrasonic Sensor
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);

  SerialUSB.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // Setup a function to be called every 5 seconds
  timer.setInterval(5000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

//for watering the crop below 60 moisture level
if(moisture_value < 60) 
  { 
    digitalWrite(motorA1,HIGH); 
    digitalWrite(motorA2,LOW); 
    delay(100); 
    digitalWrite(motorA1,LOW); 
    digitalWrite(motorA2,LOW); 
  } 
  
  //for spraying pesticide when user calls it
  int value;
  BLYNK_WRITE(V2)
  {
    value = param.asInt();
  }
  if (value == 1)
  {
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    delay(30);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
  }
}

int water_level() {

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
  cm = (duration * 0.0348) / 2;

//sending email when water level falls below 3
  if (cm < 3)
  {
    Blynk.email("Water level alert", "Fill water in the container");
  }
  return cm;

}

int pesticide_level() {

  digitalWrite(TRIGGER_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN2, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO_PIN2, INPUT);
  long duration = pulseIn(ECHO_PIN2, HIGH);

  // Convert the time into a distance
  long cm = (duration * 0.0348) / 2;

//sending email when pesticide level falls below 4
  if (cm < 4)
  {
    Blynk.email("Pesticide level alert", "Fill pesticide in the container");
  }
  return cm;


}
