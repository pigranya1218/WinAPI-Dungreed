#include "stdafx.h"
#include "CameraMoveEvent.h"

void CameraMoveEvent::processEvent(float elapsedTime)
{
	if (_remainTime <= _waitTime)
	{
		// CAMERA->setXY(_targetPos);
	}
	else
	{
		Vector2 moveDir = _targetPos - _originPos;
		float ratio = elapsedTime / _moveTime;
		moveDir = moveDir * ratio;
		CAMERA->movePivot(moveDir);
	}

	_remainTime -= elapsedTime;
}
