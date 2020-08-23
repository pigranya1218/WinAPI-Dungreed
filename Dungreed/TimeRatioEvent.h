#pragma once
#include "GameEvent.h"
class TimeRatioEvent :
    public GameEvent
{
private:
	float _ratio;

public:
	void init(float timeRatio, float remainTime);
	virtual void processEvent(float& elpasedTime) override;
};

