#pragma once
#include "stdafx.h"

class GameObject
{
protected:
	Synthesize(OBJECT_TEAM, _team, Team)
	Synthesize(Vector2, _position, Position) // x, y
	Synthesize(Vector2, _size, Size)
	Synthesize(FloatRect, _rect, Rect)
	Synthesize(bool, _active, Active)
	Synthesize(bool, _isStand, IsStand)
	Synthesize(bool, _isCollision, IsCollision) // 땅과 충돌했는지 여부

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init() {};
	virtual void release() = 0;
	virtual void update(float timeElapsed) = 0;
	virtual void render() = 0;
};

