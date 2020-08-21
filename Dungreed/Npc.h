#pragma once
#include "GameObject.h"

class NpcManager;
class UIManager;

enum class NPC_TYPE : int
{
	RESTAURANT, // 식당
	SHOP, // 상점
	GATE, // 게이트
	END
};

class Npc : public GameObject
{
protected:
	NpcManager* _npcMgr;
	UIManager* _uiMgr;

	NPC_TYPE _type;

	bool _isActiveInteraction; // 활성화중인가? (상호작용중인지 판단)
	bool _isClose; // 플레이어가 가까이 있는가
	DIRECTION _direction; // 바라보는 방향

	// FOR DIALOGUE
	string _name; // 이름
	string _bodyDialogue; // 본문 글
	vector<string> _selectDialogues; // 선택지

	Vector2 _force; // 받고 있는 힘

	Image* _mapIcon; // 지도 UI에서 보여질 그림
	Image* _miniMapIcon;

public:
	void setNpcManager(NpcManager* npcMgr) { _npcMgr = npcMgr; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }

	virtual void init(Vector2 pos, DIRECTION direction) {};
	virtual void update(float timeElapsed);
	virtual void render();
	virtual void interaction() {} // 상호작용 키를 눌렀을 때 실행될 것 (오버라이드하여 사용)
	bool isActiveInteraction() { return _isActiveInteraction; }
	void setActiveInteraction(bool activeInteraction) { _isActiveInteraction = activeInteraction; }
	
	virtual void clickMenu(int menuIndex) {}; // Dialogue 창에서 메뉴를 클릭함

	string getName() { return _name; }
	string getBodyDialogue() { return _bodyDialogue; }
	vector<string> getSelectDialogues() { return _selectDialogues; }
	Image* getMapIcon() { return _mapIcon; };
	Image* getMiniMapIcon() { return _miniMapIcon; };
	
	NPC_TYPE getType() { return _type; }
};

