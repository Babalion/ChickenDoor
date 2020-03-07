#include "../lib/virtualMotor.hpp"

VirtualMotor::VirtualMotor()
{
}

VirtualMotor::~VirtualMotor()
{
}

MotorState VirtualMotor::getState(){
    return currentState;
}