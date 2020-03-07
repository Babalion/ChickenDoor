#pragma once

#include <Arduino.h>

enum MotorCommand {cmdUp,cmdDown,cmdN};
enum MotorState {isUp,isDown,isN};

class VirtualMotor
{
protected:
    MotorState currentState;
public:
    VirtualMotor();
    ~VirtualMotor();

    MotorState getState();
    virtual void attach(byte,byte)=0;
    virtual void command(MotorCommand)=0;
};
