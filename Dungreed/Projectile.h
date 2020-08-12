#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
protected:
	OBJECT_TEAM _team;

public:
	virtual void fire() = 0;
	virtual void move() = 0;
};