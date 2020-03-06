#pragma once
#include "virtualMotor.hpp"

class MotorHBridge : public VirtualMotor
{
private:
    byte pinLeft;
    byte pinRight;

public:
    MotorHBridge();
    ~MotorHBridge();
    void attach(byte,byte);
    void command(MotorCommand);
};
