#include "endSwitch.hpp"

EndSwitch::EndSwitch(byte pin) : pin(pin)
{
    pinMode(pin, INPUT);
    debouncer = Bounce();
    debouncer.attach(pin);
    debouncer.interval(5); // interval in ms
}

EndSwitch::~EndSwitch()
{
}

bool EndSwitch::isTriggered()
{
    debouncer.update();
    if (debouncer.read() == LOW)
    {
        return true;
    }
    else
    {
        return false;
    }
}