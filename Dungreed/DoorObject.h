#pragma once
#include "Object.h"

class Player;

class DoorObject : public Object
{
private:
	struct tagOpenEffect
	{
		Vector2 pos;
		float remainTime;
	};


private:
	Image* _img;
	Player* _player;

	DIRECTION _direction; // 어디를 막는 문인지

	Animation* _ani;

	bool _isOpen;
	vector<tagOpenEffect> _openTextures;

	float _delayTime;

private:

public:
	void init(Vector2 pos, DIRECTION direction); // 좌우 막는 문은 ㅡ 모양, 상하 막는 문은 | 모양
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;

	void setOpen(bool isOpen);
	bool isOpen() { return _isOpen; }

};

