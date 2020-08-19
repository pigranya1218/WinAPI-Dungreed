#pragma once
#include "CameraEvent.h"

class CameraShakeEvent :
	public CameraEvent
{
private:
	float _power;
	float _elapsedTime;

public:
	CameraShakeEvent(float power, float remainTime)
		: _power(power)
	{
		_type = CAMERA_EVENT_TYPE::SHAKE;
		_remainTime = remainTime;
		_elapsedTime = 0;
	}

	virtual void processEvent(float elapsedTime) override;

	float getPower() { return _power; }
	void setPower(float power) { _power = power; }
};

