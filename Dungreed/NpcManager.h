#pragma once
#include "Npc.h"

class Stage;
class UIManager;
struct tagShowNpc;

class NpcManager
{
private:
	Stage* _stage;
	UIManager* _uiMgr;
	vector<Npc*> _npcs;

public:
	void setStage(Stage* stage) { _stage = stage; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	void spawnNpc(NPC_TYPE type, Vector2 pos, DIRECTION direction);

	Vector2 getPlayerPos();

	void moveTo(GameObject* gameObject, Vector2 moveDir);

	vector<tagShowNpc> getNpcInfos();
};

