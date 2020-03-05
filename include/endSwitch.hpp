#pragma once

#include <Arduino.h>
#include <Bounce2.h>


//This class represents an endswitch for a motor
class EndSwitch
{
private:
    //for debouncing
    byte pin;
    int index=0;
    Bounce debouncer;
public:
    EndSwitch(byte pin);
    ~EndSwitch();

    //reads state of the endswitch
    //true, if endswitch is triggered
    //false, else
    bool isTriggered(){}
};