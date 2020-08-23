#pragma once
#include "Object.h"

class Player;

class ItemObject : public Object
{
private:
	Player* _player;

	Item* _item;

	Vector2 _force;
	float _radian;
	float _power;

public:
	void init(Item* item, Vector2 pos, float power, float radian);
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;
};

