#pragma once
#include "Item.h"

class TestScene;

class Matchlock : public Item
{
private:
protected:
	TestScene* _testScene;
	FloatRect _hand01, _hand02;
public:
	Matchlock(Vector2 pos, DIRECTION dir);
	~Matchlock();

	void init();
	void update(Vector2 pos, DIRECTION dir);
	void release();
	void render();

	void setTestScene(TestScene* testScene) { _testScene = testScene; }
};

