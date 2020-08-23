#include "stdafx.h"
#include "CameraFillEvent.h"

void CameraFillEvent::processEvent(float elapsedTime)
{
	_remainTime -= elapsedTime;
}

void CameraFillEvent::render()
{
	if (_remainTime <= _displayTime + _closeTime + _enterTime)
	{
		float alpha = 1;
		if (_remainTime >= _closeTime + _enterTime)
		{
			alpha = min(alpha, (1 - (_remainTime - (_closeTime + _enterTime))) / _closeTime);
		}
		else
		{
			alpha = min(alpha, _remainTime / _closeTime);
		}
		
		for (int i = 0; i < _fillRect.size(); i++)
		{
			D2D_RENDERER->fillRectangle(_fillRect[i], GetRValue(_color), GetGValue(_color), GetBValue(_color), alpha);
		}
	}
}
