#include "virtualMotor.hpp"
#include "motorHBridge.hpp"

motorHBridge::motorHBridge(byte pinLeft, byte pinRight) : pinLeft(pinLeft), pinRight(pinRight)
{
    pinMode(pinLeft, OUTPUT);
    pinMode(pinRight, OUTPUT);
}

motorHBridge::~motorHBridge()
{
}

void motorHBridge::command(MotorCommand cmd)
{
    switch (cmd)
    {
    case cmdUp:
        digitalWrite(pinLeft, HIGH);
        digitalWrite(pinRight, LOW);
        currentState=isUp;
        break;
    case cmdDown:
        digitalWrite(pinLeft, LOW);
        digitalWrite(pinRight, HIGH);
        currentState=isDown;
        break;
    case cmdN:
        digitalWrite(pinLeft, LOW);
        digitalWrite(pinRight, LOW);
        currentState=isN;
        break;
    default:
        break;
    }
}