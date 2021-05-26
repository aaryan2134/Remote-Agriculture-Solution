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

DHT11 dht11(D7);  // creating the object sensor on pin 'D7'

//Use your authorization token after creating new project in Blynk App
char auth[] = "authorization token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your ssid";
char pass[] = "your password";

//constants
int LDRpin = A0; // select the input pin for LDR
int LDRvalue = 0; // variable to store the value coming from the LDR
int lux = 0;         //to store the intensity of light in lux

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

}
void setup() {
  SerialUSB.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
