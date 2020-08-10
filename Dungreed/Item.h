#pragma once
#include "stdafx.h"
#include "Player.h"

class TestScene;

class Item
{
private:
	TestScene* _testScene;
	char _buffer[128];
protected:
	Image* _img;
	Vector2 _position;
	Player* _player;
	RECT _hand01, _hand02;
	bool _isLeft;
public:
	Item() {};
	Item(Vector2 pos, DIRECTION dir) {};
	~Item();

	void init();
	void update(Vector2 pos, DIRECTION dir);
	void release();
	void render();

	void setTestScene(TestScene* testScene) { _testScene = testScene; }
	//void setWeaponPosition(float x, float y) { _x = x, _y = y; }
	//void PlayerLink() {}
};
