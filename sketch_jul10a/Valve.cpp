/* -*- c -*- */

// Drive a pair of motors connected to a L293NE or SN754410 H-bridge chip.
// http://itp.nyu.edu/physcomp/Labs/DCMotorControl
// Each motor has two logic pins and one enable pin.
// The enable pin is the analog pin that controls the speed;
// the logic pins control the direction; setting both to the
// same value stops the motor.
// 

// Represent each motor's speed as an integer between -255 and 255.
// We'll map that into appropriate signals to send to the motor.
// When speed > 0, direction will have logic pin 0 high, 1 low;
// speed < 0 will be the reverse.

#include "Valve.h"

Valve::Valve(int enablePin, int logicPin0, int logicPin1)
{
    mEnablePin = enablePin;
    mLogicPins[0] = logicPin0;
    mLogicPins[1] = logicPin1;
}

void Valve::init()
{
    pinMode(mEnablePin, OUTPUT);
    pinMode(mLogicPins[0], OUTPUT);
    pinMode(mLogicPins[1], OUTPUT);

    mState = false;
    analogWrite(mEnablePin, 1);
    digitalWrite(mLogicPins[0], LOW);
    digitalWrite(mLogicPins[1], LOW);
}

#define DEBUG 1

//
// turns on valve
//
void Valve::setRate(int rate)
{
#ifdef DEBUG
    Serial.print("Valve enablePin");
    Serial.println(mEnablePin);
    Serial.print("setState ");
    Serial.print(rate);
    Serial.print(" (currently ");
    Serial.print(mRate);
    Serial.println(")");
#endif
	
	mRate = rate;
	if(rate > 0)
	{
		digitalWrite(mLogicPins[0], HIGH);
	}
	else
	{
		digitalWrite(mLogicPins[0], LOW);
	}  
}
