#pragma once
#include "GameObject.h"

class NpcManager;
class UIManager;

enum class NPC_TYPE : int
{
	RESTAURANT, // 식당
	SHOP, // 상점
};

class Npc : public GameObject
{
protected:
	NpcManager* _npcMgr;
	UIManager* _uiMgr;

	bool _isActive; // 활성화중인가? (상호작용중인지 판단)
	bool _isClose; // 플레이어가 가까이 있는가
	DIRECTION _direction; // 바라보는 방향

	// FOR DIALOGUE
	string _name; // 이름
	string _bodyDialogue; // 본문 글
	vector<string> _selectDialogues; // 선택지

public:
	void setNpcManager(NpcManager* npcMgr) { _npcMgr = npcMgr; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }

	virtual void init(Vector2 pos, DIRECTION direction) {};
	bool isActive() { return _isActive; }
	
	virtual void clickMenu(int menuIndex) {}; // Dialogue 창에서 메뉴를 클릭함
	string getName() { return _name; }
	string getBodyDialogue() { return _bodyDialogue; }
	vector<string> getSelectDialogues() { return _selectDialogues; }
};

