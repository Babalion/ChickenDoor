#include "..\lib\motorServo.hpp"

MotorServo::MotorServo(){
    
}

MotorServo::~MotorServo()
{
}

// only uses first pin as PWM-Pin
void MotorServo::attach(byte _PWM_Pin,byte none){
    PWM_Pin=_PWM_Pin;
    myServo.attach(9);
    command(cmdN);
}

void MotorServo::command(MotorCommand cmd)
{
    switch (cmd)
    {
    case cmdUp:
        myServo.write(180);
        currentState=isUp;
        break;
    case cmdDown:
        myServo.write(-180);
        currentState=isDown;
        break;
    case cmdN:
        myServo.detach();
        digitalWrite(9,HIGH);
        currentState=isN;
        break;
    default:
        break;
    }
}