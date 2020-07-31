#include "stdafx.h"
#include "CameraShakeEvent.h"

void CameraShakeEvent::processEvent()
{
	if (_direction == DIRECTION::LEFT)
	{
		CAMERA_MANAGER->movePivot(0, _power);
		_direction = DIRECTION::RIGHT;
	}
	else
	{
		_direction = DIRECTION::LEFT;
	}

	if (_elapsedTime < 0)
	{
		_elapsedTime = _shakePerTime;
		if (_direction == DIRECTION::LEFT)
		{
			_direction = DIRECTION::RIGHT;
		}
		else
		{
			_direction = DIRECTION::LEFT;
		}
	}

	_elapsedTime -= TIME_MANAGER->getElapsedTime();
	_remainTime -= TIME_MANAGER->getElapsedTime();
}
