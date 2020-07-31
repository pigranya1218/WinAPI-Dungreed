#pragma once

class CameraEvent
{
protected:
	float _remainTime;

public:
	float getRemainTime() { return _remainTime; }
	virtual void processEvent();
};

