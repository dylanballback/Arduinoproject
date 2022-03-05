#include "Arduino.h"
#include <Wire.h> 
#include <PWM.h>

const int nidecBrake = 8;      // Brake
const int nidecDirection = 7;  // CW/CCW Nidec Motor
const int ledsDirection = 6;   // Green LED direction indicators
const int ledsBrake = 5;       // Red LED direction indicators
const int nidecPWM = 9;        // Nidec Motor PWSerial.begin(9600);
    
void setup(){
    Serial.begin(112500);
    //*************************** Nidec 24H677H010 BLDC Motor Setup *****************************
    // PWM.h Setup
    InitTimersSafe();
    // The Nidec 24H677 BLDC Motor requires a PWM frequency of 20KHz to 25KHz
    bool success = SetPinFrequencySafe(nidecPWM, 20000);

    //set the Nidec motor control pins 
    pinMode(nidecBrake, OUTPUT);
    pinMode(nidecDirection,OUTPUT);
    pinMode(ledsDirection,OUTPUT);
    pinMode(ledsBrake,OUTPUT);
    pinMode(nidecPWM,OUTPUT);
  
    // Output initial state values
    digitalWrite(nidecDirection,LOW); // Nidec Direction CCW
    digitalWrite(ledsDirection,LOW); //Green LED OFF // Direction CCW
    digitalWrite(nidecBrake,LOW); // Nidec motor brake is O
    digitalWrite(ledsBrake,HIGH); //Red LED ON // Brake ON
    analogWrite(nidecPWM,400); // Motor Stop PWM Signal

    Serial.println("Welcome! Beginning transmission");
    pinMode(LED_BUILTIN,OUTPUT);
}
void loop() 
{
    digitalWrite(nidecBrake,HIGH);
    digitalWrite(ledsBrake,LOW);
    digitalWrite(nidecDirection,LOW);
    digitalWrite(ledsDirection,LOW);
    analogWrite(nidecPWM, 200);
    delay(2000);
    Serial.println("half speed");
    analogWrite(nidecPWM, 100);
    delay(2000);
    Serial.println("three fourths speed");
    analogWrite(nidecPWM, 400);
    delay(4000);
    Serial.println("Stopped");
}
