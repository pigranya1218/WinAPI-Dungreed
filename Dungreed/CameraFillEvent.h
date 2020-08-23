#pragma once
#include "CameraEvent.h"
class CameraFillEvent : public CameraEvent
{
private:
	vector<FloatRect> _fillRect;
	float _waitingTime; // ��ٸ��� �ð�
	float _enterTime; // ���� ������ �Ǹ鼭 ��Ÿ���� �ð�
	float _displayTime; // �׸��� �ð�
	float _closeTime; // ���� ������ �Ǹ鼭 ������� �ð�
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

