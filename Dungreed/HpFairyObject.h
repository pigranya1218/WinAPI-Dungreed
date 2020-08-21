#pragma once
#include "Object.h"

class Player;

class HpFairyObject : public Object
{
private:
	Image* _img;
	Player* _player;

	int _value;
	Animation* _ani;

private:
	void getFairyImage();

public:
	void init(float value, Vector2 pos);
	virtual void release() override;
	virtual void update(float elapsedTime) override;
	virtual void render() override;

};

