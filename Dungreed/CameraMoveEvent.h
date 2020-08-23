#pragma once
#include "CameraEvent.h"
class CameraMoveEvent :
    public CameraEvent
{
private:
	Vector2 _originPos;
	Vector2 _targetPos;
	float _moveTime;
	float _waitTime;

public:
	CameraMoveEvent(Vector2 pos, float moveTime, float waitTime)
		: _originPos(CAMERA->getXY()), _targetPos(pos), _moveTime(moveTime), _waitTime(waitTime)
	{
		_type = CAMERA_EVENT_TYPE::MOVE;
		_remainTime = _moveTime + _waitTime;
	}

	virtual void processEvent(float elapsedTime) override;
};

