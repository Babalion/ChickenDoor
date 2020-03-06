#include <Arduino.h>
#include "../include/motorHBridge.hpp"
#include "../include/endSwitch.hpp"
#include <Bounce2.h>

enum DoorPosition
{
	DoorUp,
	DoorDown,
	DoorMiddle
};

EndSwitch EsUp = EndSwitch();
EndSwitch EsDown = EndSwitch();
MotorHBridge DoorMotor = MotorHBridge();
DoorPosition dPos;
void updateDoorPos()
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
	buttonDoorUp.attach(5);
	buttonDoorDown.attach(6);
	buttonDoorUp.interval(10);
	buttonDoorDown.interval(10);

	EsUp.attach(1);
	EsDown.attach(2);
	DoorMotor.attach(3, 4);
	updateDoorPos();
}

void loop()
{
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
			unsigned long start = millis();
			while (dPos == DoorUp && DoorMotor.getState() == isDown && (millis() - start) < 60E3)
			{
				updateDoorPos();
				buttonDoorUp.update();
				buttonDoorDown.update();
				if (buttonDoorDown.risingEdge() || buttonDoorUp.risingEdge())
				{
					DoorMotor.command(cmdN);
				}
			}
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
			unsigned long start = millis();
			while (dPos == DoorMiddle && DoorMotor.getState() == isUp && (millis() - start) < 60E3)
			{
				updateDoorPos();
				buttonDoorUp.update();
				buttonDoorDown.update();
				if (buttonDoorDown.risingEdge() || buttonDoorUp.risingEdge())
				{
					DoorMotor.command(cmdN);
				}
			}
			break;
		case isDown:
			unsigned long start = millis();
			while (dPos == DoorMiddle && DoorMotor.getState() == isDown && (millis() - start) < 60E3)
			{
				updateDoorPos();
				buttonDoorUp.update();
				buttonDoorDown.update();
				if (buttonDoorDown.risingEdge() || buttonDoorUp.risingEdge())
				{
					DoorMotor.command(cmdN);
				}
			}
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
			unsigned long start = millis();
			while (dPos == DoorDown && DoorMotor.getState() == isUp && (millis() - start) < 60E3)
			{
				updateDoorPos();
				buttonDoorUp.update();
				buttonDoorDown.update();
				if (buttonDoorDown.risingEdge() || buttonDoorUp.risingEdge())
				{
					DoorMotor.command(cmdN);
				}
			}
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