#pragma once
#include "GameEvent.h"

// ȭ���� ��ο��� ������� ��
class RoomToRoomEvent : public GameEvent
{
private:
	COLORREF _color;
public:
	void init(COLORREF color, float remainTime);
	virtual void processEvent(float& elpasedTime) override;
	virtual void render() override;
};

