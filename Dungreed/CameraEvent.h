#pragma once

enum class CAMERA_EVENT_TYPE : int
{
	SHAKE = 0,
	MOVE = 1,
	FILL = 2,
	END
};

class CameraEvent
{
protected:
	CAMERA_EVENT_TYPE _type;
	float _remainTime;

public:
	CAMERA_EVENT_TYPE getType() { return _type; }
	float getRemainTime() { return _remainTime; }
	void setRemainTime(float time) { _remainTime = time; }
	virtual void processEvent(float elapsedTime);
	virtual void render() {}
};

