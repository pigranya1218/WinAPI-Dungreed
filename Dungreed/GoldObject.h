#pragma once
#include "Object.h"

class Player;

class GoldObject : public Object
{
private:
	Image* _img;
	Player* _player;

	Vector2 _force;
	float _radian;
	float _power;

	float _value;
	Animation* _ani;

private:
	void getGoldImage();

public:
	void init(float value, Vector2 pos, float power, float radian);
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;
};

