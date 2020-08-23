#include "stdafx.h"
#include "RoomToRoomEvent.h"

void RoomToRoomEvent::init(COLORREF color, float remainTime)
{
	_type = GAME_EVENT_TYPE::R2R;
	_color = color;
	_totalTime= _remainTime = remainTime;
}

void RoomToRoomEvent::processEvent(float& elpasedTime)
{
	_remainTime = max(0, _remainTime - elpasedTime);
}

void RoomToRoomEvent::render()
{
	float alpha = _remainTime / _totalTime;
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), GetRValue(_color), GetGValue(_color), GetBValue(_color), alpha);
}
