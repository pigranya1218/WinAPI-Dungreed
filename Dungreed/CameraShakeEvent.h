#pragma once
#include "CameraEvent.h"

class CameraShakeEvent :
	public CameraEvent
{
private:
	float _power;
	float _shakePerTime;
	float _elapsedTime;
	DIRECTION _direction;

public:
	CameraShakeEvent(float power, float shakePerTime, float remainTime)
		: _power(power), _shakePerTime(shakePerTime), _direction(DIRECTION::LEFT)
	{
		_remainTime = remainTime;
		_elapsedTime = 0;
	}
	virtual void processEvent();
};

