#pragma once

enum class GAME_EVENT_TYPE
{
	R2R,
	TIME_RATIO,
	END
};

class GameEvent
{
protected:
	GAME_EVENT_TYPE _type;
	float _remainTime;
	float _totalTime;
	
public:
	GAME_EVENT_TYPE getType() const { return _type; }
	float getRemainTime() const { return _remainTime; }
	void setRemainTime(float time) { _remainTime = time; }
	float getTotalTime() const { return _totalTime; }
	void setTotalTime(float time) { _totalTime = time; }
	virtual void processEvent(float& elapsedTime) {}
	virtual void render() {}
};

