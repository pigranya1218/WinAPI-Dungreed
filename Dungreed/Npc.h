#pragma once
#include "GameObject.h"

class NpcManager;
class UIManager;

enum class NPC_TYPE : int
{
	RESTAURANT, // �Ĵ�
	SHOP, // ����
	GATE, // ����Ʈ
	CHEST_BASIC, // �Ϲ����� ���� (�Ϲ�)
	CHEST_BLUE, // �Ϲ����� ����  (�Ϲ� ~ ���)
	CHEST_YELLOW, // �Ϲ����� ���� (��� ~ ���)
	CHEST_BOSS, // ���� ���� (��� ~ ����)
	ENTRANCE, // �Ա�
	EXIT, // �ⱸ
	ABILITY, //�Ʒ���
	COSTUME, // �ǻ��
	END
};

class Npc : public GameObject
{
protected:
	NpcManager* _npcMgr;
	UIManager* _uiMgr;

	NPC_TYPE _type;

	bool _isActiveInteraction; // Ȱ��ȭ���ΰ�? (��ȣ�ۿ������� �Ǵ�)
	bool _isClose; // �÷��̾ ������ �ִ°�
	DIRECTION _direction; // �ٶ󺸴� ����

	// FOR DIALOGUE
	wstring _name; // �̸�
	wstring _bodyDialogue; // ���� ��
	vector<wstring> _selectDialogues; // ������

	Vector2 _force; // �ް� �ִ� ��

	Image* _mapIcon; // ���� UI���� ������ �׸�
	Image* _miniMapIcon;

public:
	void setNpcManager(NpcManager* npcMgr) { _npcMgr = npcMgr; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }

	virtual void init(Vector2 pos, DIRECTION direction) {};
	virtual void update(float timeElapsed);
	virtual void render();
	virtual void interaction() {} // ��ȣ�ۿ� Ű�� ������ �� ����� �� (�������̵��Ͽ� ���)
	bool isActiveInteraction() { return _isActiveInteraction; }
	void setActiveInteraction(bool activeInteraction) { _isActiveInteraction = activeInteraction; }
	
	virtual void clickMenu(int menuIndex) {}; // Dialogue â���� �޴��� Ŭ����

	wstring getName() { return _name; }
	wstring getBodyDialogue() { return _bodyDialogue; }
	vector<wstring> getSelectDialogues() { return _selectDialogues; }
	Image* getMapIcon() { return _mapIcon; };
	Image* getMiniMapIcon() { return _miniMapIcon; };
	
	NPC_TYPE getType() { return _type; }
};

