#pragma once
#include "GameObject.h"

class NpcManager;
class UIManager;

enum class NPC_TYPE : int
{
	RESTAURANT, // �Ĵ�
	SHOP, // ����
};

class Npc : public GameObject
{
protected:
	NpcManager* _npcMgr;
	UIManager* _uiMgr;

	bool _isActive; // Ȱ��ȭ���ΰ�? (��ȣ�ۿ������� �Ǵ�)
	bool _isClose; // �÷��̾ ������ �ִ°�
	DIRECTION _direction; // �ٶ󺸴� ����

	// FOR DIALOGUE
	string _name; // �̸�
	string _bodyDialogue; // ���� ��
	vector<string> _selectDialogues; // ������

public:
	void setNpcManager(NpcManager* npcMgr) { _npcMgr = npcMgr; }
	void setUIManager(UIManager* uiMgr) { _uiMgr = uiMgr; }

	virtual void init(Vector2 pos, DIRECTION direction) {};
	bool isActive() { return _isActive; }
	
	virtual void clickMenu(int menuIndex) {}; // Dialogue â���� �޴��� Ŭ����
	string getName() { return _name; }
	string getBodyDialogue() { return _bodyDialogue; }
	vector<string> getSelectDialogues() { return _selectDialogues; }
};

