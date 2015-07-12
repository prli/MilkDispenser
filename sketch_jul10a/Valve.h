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

#ifndef Valve_h
#define Valve_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <wiring.h>
#endif

// This def causes trouble on some versions of Arduino:
#undef abs

class Valve {
  public:
    int mEnablePin;
    int mLogicPins[2];
	bool mState;
	int mRate;
	
    Valve(int enablePin, int logicPin1, int logicPin2);
    void init();
    void setRate(int rate);
};

typedef class Valve Valve;

#endif /* Valve_h */