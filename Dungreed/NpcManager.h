#pragma once
#include "Npc.h"

class NpcManager
{
private:
	vector<Npc*> _npcs;

public:
	void init();
	void release();
	void update(float elapsedTime);
	void render();
};

