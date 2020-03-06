#pragma once
#include "virtualMotor.hpp"

class motorHBridge : public VirtualMotor
{
private:
    byte pinLeft;
    byte pinRight;

public:
    motorHBridge(byte, byte);
    ~motorHBridge();
    void command(MotorCommand);
};
