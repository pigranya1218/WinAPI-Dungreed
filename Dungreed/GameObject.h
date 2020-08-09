#pragma once
#include "stdafx.h"

class GameObject
{
	Synthesize(OBJECT_TEAM,_team,Team)
	Synthesize(Vector2, _position, Position) // x, y
	Synthesize(Vector2, _size,Size)
	Synthesize(FloatRect, _rect,Rect)
	Synthesize(bool, _active,Active)
	Synthesize(DIRECTION, _direction, Direction)

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();
};

