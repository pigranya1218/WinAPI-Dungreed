#pragma once
#include "GameEvent.h"

// 화면이 어두웠다 밝아지는 거
class RoomToRoomEvent : public GameEvent
{
private:
public:
	void init(float remainTime);
	virtual void processEvent(float elpasedTime) override;
	virtual void render() override;
};

