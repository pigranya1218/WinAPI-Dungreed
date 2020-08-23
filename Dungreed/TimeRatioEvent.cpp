#include "stdafx.h"
#include "TimeRatioEvent.h"

void TimeRatioEvent::init(float timeRatio, float remainTime)
{
	_type = GAME_EVENT_TYPE::TIME_RATIO;
	_ratio = timeRatio;
	_totalTime = _remainTime = remainTime;
}

void TimeRatioEvent::processEvent(float& elpasedTime)
{
	_remainTime = max(0, _remainTime - elpasedTime);
	elpasedTime *= _ratio;
}
