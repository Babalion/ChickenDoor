#include "../lib/virtualMotor.hpp"
#include "../lib/motorHBridge.hpp"

MotorHBridge::MotorHBridge()
{}

MotorHBridge::~MotorHBridge()
{
}

void MotorHBridge::attach(byte pinL,byte pinR){
    pinLeft=pinL;
    pinRight=pinR;
    pinMode(pinLeft, OUTPUT);
    pinMode(pinRight, OUTPUT);
}

void MotorHBridge::command(MotorCommand cmd)
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