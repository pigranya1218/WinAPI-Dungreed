#pragma once
#include "Item.h"
#include "stdafx.h"
#include "Player.h"

class ItemManager
{
private:
	vector<Item*>	_VItem;
public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void spawnItem();
	void pickUp();
};

