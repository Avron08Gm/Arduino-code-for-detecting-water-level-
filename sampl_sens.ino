#include<SoftwareSerial.h>
SoftwareSerial gsm(3,2); // connect TX pin of GSM to digital pin 3 , RX to pin 2 and ground to GND of Arduino board 
int trigPin = 9; // connect trig pin of the sensor to pin 9 of Arduino 
int echoPin = 10; // connect echo pin of the sensor to pin 10 of Arduino
int led = 13; // connect led to pin 13 of Arduino (if necessary)
int max_height = 300; // max height of the water level to reach (in centimetres)

void setup() {
  Serial.begin(9600);
  // Setup the led, sensor and GSM shield 
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(20000); // wait for 20 seconds for the GSM to connect to a network (it could be more or less depending upon the network strength)
  gsm.begin(9600);
}

void loop() {
  long dur, dist;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  dur = pulseIn(echoPin, HIGH);
  dist = (dur/2)/29.1;
  delay(10); 
  if((dist<=max_height)) 
  {
    gsm.println("AT+CMGF=1");
    delay(1000);
    gsm.println("AT+CMGS=\"+91----------\"\r"); //replace '-' by the number required
    delay(1000);
    gsm.println("Water level is high.");
    delay(100);
    gsm.println((char)26);
    delay(1000);
  }
  delay(100);
}
