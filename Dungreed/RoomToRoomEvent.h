#pragma once
#include "GameEvent.h"

// ȭ���� ��ο��� ������� ��
class RoomToRoomEvent : public GameEvent
{
private:
public:
	void init(float remainTime);
	virtual void processEvent(float elpasedTime) override;
	virtual void render() override;
};

