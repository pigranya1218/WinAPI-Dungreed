#include "stdafx.h"
#include "CameraShakeEvent.h"

void CameraShakeEvent::processEvent(float elapsedTime)
{
	if (_elapsedTime < 0)
	{
		if (CONFIG_MANAGER->isCameraShake())
		{

			Vector2 moveForce = Vector2(RANDOM->getFromFloatTo(-_power, _power), RANDOM->getFromFloatTo(-_power, _power));
			CAMERA->movePivot(moveForce);
		}
		_elapsedTime = 0.05;
	}

	_elapsedTime -= elapsedTime;
	_remainTime -= elapsedTime;
}
