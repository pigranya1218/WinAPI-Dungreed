#pragma once
#include "Npc.h"

class Stage;
class UIManager;
class ObjectManager;
struct tagShowNpc;

class NpcManager
{
private:
	Stage* _stage;
	ObjectManager* _objectMgr;
	UIManager* _uiMgr;
	vector<Npc*> _npcs;

public:
	void setStage(Stage* stage) { _stage = stage; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }
	void setObjectManager(ObjectManager* objectMgr) { _objectMgr = objectMgr; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	void spawnNpc(NPC_TYPE type, Vector2 pos, DIRECTION direction);

	Vector2 getPlayerPos();

	void moveTo(GameObject* gameObject, Vector2 moveDir);

	vector<tagShowNpc> getNpcInfos();
	vector<Npc*> getNpcs() { return _npcs; };

	void moveRoom(Vector2 pos); // for gate..
	void nextStage(); // for gate
	Vector2 getGatePos();

	void setShowPlayer(bool showPlayer);
	void showRestaurantUI();
	void showShopUI();
	void showAbilityUI();
	void showCostumeUI();
};

