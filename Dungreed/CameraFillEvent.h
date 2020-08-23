#pragma once
#include "CameraEvent.h"
class CameraFillEvent : public CameraEvent
{
private:
	vector<FloatRect> _fillRect;
	float _waitingTime; // 기다리는 시간
	float _enterTime; // 알파 렌더링 되면서 나타나는 시간
	float _displayTime; // 그리는 시간
	float _closeTime; // 알파 렌더링 되면서 사라지는 시간
	COLORREF _color;

public:
	CameraFillEvent(vector<FloatRect> fillRect, float waitingTime, float enterTime, float displayTime, float closeTime, COLORREF color)
		: _fillRect(fillRect), _waitingTime(waitingTime), _enterTime(enterTime), _displayTime(displayTime), _closeTime(closeTime), _color(color)
	{
		_type = CAMERA_EVENT_TYPE::FILL;
		_remainTime = _waitingTime + _enterTime + _displayTime + _closeTime;
	}

	virtual void processEvent(float elapsedTime) override;
	virtual void render() override;
};

