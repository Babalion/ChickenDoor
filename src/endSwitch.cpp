#include "../lib/endSwitch.hpp"

EndSwitch::EndSwitch(){
    debouncer = Bounce();
}

void EndSwitch::attach(byte _pin)
{
    pin=_pin;
    pinMode(pin, INPUT);
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