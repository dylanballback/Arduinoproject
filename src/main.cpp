#include "Arduino.h"
#include <Wire.h> 
#include <PWM.h>

const int nidecBrake = 8;      // Brake
const int nidecDirection = 7;  // CW/CCW Nidec Motor
const int ledsDirection = 6;   // Green LED direction indicators
const int ledsBrake = 5;       // Red LED direction indicators
const int nidecPWM = 9;        // Nidec Motor PWSerial.begin(9600);
    
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  Drive Motor Function START $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// For pwm: 400 = stopped and 0 = full speed
// For dir: 0 = CCW and 1 = CW
void driveMotor(int pwm,int dir){
  //if pwm 
  digitalWrite(nidecBrake,HIGH);    // Nidec motor brake OFF
  digitalWrite(ledsBrake,LOW);      //Red LED OFF // Brake OFF
  if(dir == 0){
    analogWrite(nidecPWM, pwm);
    digitalWrite(nidecDirection,LOW); // Nidec Direction CCW
    digitalWrite(ledsDirection,LOW);  //Green LED OFF // Direction CCW
    }
  else if(dir == 1){
    analogWrite(nidecPWM, pwm);
    digitalWrite(nidecDirection,HIGH); // Nidec Direction CW
    digitalWrite(ledsDirection,HIGH);  //Green LED ON // Direction CW
    } 
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  Drive Motor Function END $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



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
    driveMotor(200,1)
    Serial.println("half speed");
    delay(2000);
    
    driveMotor(100,1)
    Serial.println("three fourths speed");
    delay(2000);
    
    driveMotor(400,1)
    Serial.println("Stopped");
    delay(5000);
    
}


