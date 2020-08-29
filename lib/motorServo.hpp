#pragma once
#include "virtualMotor.hpp"
#include <Servo.h>

// This header implements a VirtualMotor driven with a rebuild servo, which can rotate unbounded

class MotorServo : public VirtualMotor
{
private:
    byte PWM_Pin;
    Servo myServo;

public:
    MotorServo();
    ~MotorServo();
    void attach(byte,byte);
    void command(MotorCommand);
};