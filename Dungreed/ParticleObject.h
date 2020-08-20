#pragma once
#include "Object.h"
class ParticleObject : public Object
{
private:
	Image* _img;
	Vector2 _force;
	float _radian;
	float _power;
	float _degree;

public:
	void init(Image* img, Vector2 pos, float power, float radian);
	virtual void update(float elapsedTime) override;
	virtual void render() override;
};

