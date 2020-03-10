#include <Arduino.h>
#include "../lib/motorHBridge.hpp"
#include "../lib/endSwitch.hpp"
#include <Bounce2.h>

EndSwitch EsUp = EndSwitch();
EndSwitch EsDown = EndSwitch();
MotorHBridge DoorMotor = MotorHBridge();

enum DoorPosition
{
	DoorUp,
	DoorDown,
	DoorMiddle
};

DoorPosition dPos;


inline void updateDoorPos()
{
	if (EsUp.isTriggered())
	{
		dPos = DoorUp;
	}
	else if (EsDown.isTriggered())
	{
		dPos = DoorDown;
	}
	else
	{
		dPos = DoorMiddle;
	}
}

Bounce buttonDoorUp = Bounce();
Bounce buttonDoorDown = Bounce();

void setup()
{
	buttonDoorUp.attach(4);
	buttonDoorDown.attach(5);
	buttonDoorUp.interval(10);
	buttonDoorDown.interval(10);

	EsUp.attach(6);
	EsDown.attach(7);
	DoorMotor.attach(8, 9);
	updateDoorPos();
	Serial.begin(9600);
}

void runDoor(bool (*cond)())
{
	unsigned long startTime = millis();
	while (cond() && (millis() - startTime) < 60E3)
	{
		Serial.println((millis() - startTime));
		updateDoorPos();
		buttonDoorUp.update();
		buttonDoorDown.update();
		if (buttonDoorDown.risingEdge() || buttonDoorUp.risingEdge())
		{
			DoorMotor.command(cmdN);
		}
	}
	DoorMotor.command(cmdN);
}

void loop()
{
	unsigned long start = millis();
	unsigned long tmp = 0;
	if (start - tmp >= 0)
	{
		Serial.print("dPos: ");
		Serial.print(dPos);
		Serial.print(" EsUp:");
		Serial.print(EsUp.isTriggered());
		Serial.print(" EsDown:");
		Serial.print(EsDown.isTriggered());
		Serial.print(" MotorState:");
		Serial.println(DoorMotor.getState());
		tmp = start;
	}
	updateDoorPos();
	switch (dPos)
	{
	case DoorUp:
		switch (DoorMotor.getState())
		{
		case isUp:
			DoorMotor.command(cmdN);
			break;
		case isDown:
			runDoor([](){return (dPos == DoorUp && DoorMotor.getState() == isDown);});
			break;
		case isN:
			buttonDoorDown.update();
			if (buttonDoorDown.risingEdge())
			{
				DoorMotor.command(cmdDown);
			}
			break;

		default:
			break;
		}
		break;
	case DoorMiddle:
		switch (DoorMotor.getState())
		{
		case isUp:
			runDoor([](){return (dPos == DoorMiddle && DoorMotor.getState() == isUp);});
			break;
		case isDown:
			runDoor([](){return (dPos == DoorMiddle && DoorMotor.getState() == isDown);});
			break;
		case isN:
			buttonDoorUp.update();
			buttonDoorDown.update();
			if (buttonDoorDown.risingEdge())
			{
				DoorMotor.command(cmdDown);
			}
			else if (buttonDoorUp.risingEdge())
			{
				DoorMotor.command(cmdUp);
			}
			break;

		default:
			break;
		}
		break;
	case DoorDown:
		switch (DoorMotor.getState())
		{
		case isUp:
			runDoor([](){return (dPos == DoorDown && DoorMotor.getState() == isUp);});
			break;
		case isDown:
			DoorMotor.command(cmdN);
			break;
		case isN:
			buttonDoorUp.update();
			if (buttonDoorUp.risingEdge())
			{
				DoorMotor.command(cmdUp);
			}
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}
