/*
  Handsfree Faucet

  Uses a ultrasonic sensor (HC-SR04) to detect a presence of hand nearby
  (<10cm), it triggers a servo which controls the faucet opening and
  closing

  Written by Shivam Gautam
  shivamgautam1@gmail.com
  www.amritsar.tech/blog
  www.github.com/shivamgautam1

*/

#include <Servo.h>
//Setting pins for HC-SR04
const int trig = 9; //trigger Pin
const int echo = 10; //echo Pin

//Setting indicator
int led = 13;

//Set Servo
Servo faucet;

//Setting variables for distance data
long duration; //time took to receive the echo
int distance; //to store distance

void setup() {
  pinMode(trig, OUTPUT); //Set trigger pin as output
  pinMode(echo, INPUT); //Set echo pin as input
  pinMode(led, OUTPUT);
  faucet.attach(3);
  faucet.write(90);
  Serial.begin(9600); //Begin Serial communication to read distance
}

void loop() {
  digitalWrite(trig, LOW); //Clear the trig
  delayMicroseconds(2);

  digitalWrite(trig, HIGH); //trig HIGH for 10 secs
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH); //returns sound wave travel time in uSec

  distance = duration*0.034/2; //distance = time x Speed

  if(distance<10){
      faucet.write(180);
      digitalWrite(led, HIGH);
    }
  else{
      faucet.write(90);
      digitalWrite(led, LOW);
    }
  //print distance on Serial
  Serial.print("Distance: ");
  Serial.println(distance);
}
