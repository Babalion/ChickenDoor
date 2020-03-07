#pragma once

#include <Arduino.h>
#include <Bounce2.h>

//This class represents an endswitch for a motor
class EndSwitch
{
private:
    //for debouncing
    byte pin = 0;
    Bounce debouncer;

public:
    EndSwitch();
    ~EndSwitch();

    //initializes the pin to the endswitch
    void attach(byte Pin);

    //reads state of the endswitch
    //true, if endswitch is triggered
    //false, else
    bool isTriggered();
};