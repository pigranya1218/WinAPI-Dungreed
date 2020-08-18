#pragma once
#include "Npc.h"

class Stage;

class NpcManager
{
private:
	Stage* _stage;
	vector<Npc*> _npcs;

public:
	void setStage(Stage* stage) { _stage = stage; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	void spawnNpc(NPC_TYPE type, Vector2 pos, DIRECTION direction);

	Vector2 getPlayerPos();
};

