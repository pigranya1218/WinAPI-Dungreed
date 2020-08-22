#pragma once

enum class GAME_EVENT_TYPE
{
	R2R,
	END
};

class GameEvent
{
protected:
	GAME_EVENT_TYPE _type;
	float _remainTime;
	
public:
	void processEvent(float elapsedTime);
	void render();
};

