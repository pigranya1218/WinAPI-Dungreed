#include "stdafx.h"
#include "RoomToRoomEvent.h"

void RoomToRoomEvent::init(float remainTime)
{
	_type = GAME_EVENT_TYPE::R2R;
	_remainTime = remainTime;
	_totalTime = remainTime;
}

void RoomToRoomEvent::processEvent(float elpasedTime)
{
	_remainTime = max(0, _remainTime - elpasedTime);
}

void RoomToRoomEvent::render()
{
	float alpha = _remainTime / _totalTime;
	D2D_RENDERER->fillRectangle(FloatRect(0, 0, WINSIZEX, WINSIZEY), 0, 0, 0, alpha);
}
