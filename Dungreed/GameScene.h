#pragma once
#include "GameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"



class GameScene : public GameNode
{
private:
	float _timeSpeed; // �ð� ���, 1 = �⺻ �ӵ�

	Player* _player;
	StageManager* _stageMgr;
	UIManager* _uiMgr;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	// �ʱ� ���� ���� �Լ�
	void loadInfo(tagLoadInfo const info);

	// �÷��̾� ���� �Լ�
	Vector2 getPlayerPos() { return _player->getPosition(); }


	// �������� ���� �Լ�
	void moveTo(GameObject* object, Vector2 moveDir);
	void attack(FloatRect* rect, tagAttackInfo* info);
	void attack(FloatCircle* circle, tagAttackInfo* info);
	void attack(Projectile* projectile, tagAttackInfo* info);

	// UI ���� �Լ�



};

