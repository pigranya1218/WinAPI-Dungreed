#pragma once
#include "GameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"



class GameScene : public GameNode
{
private:
	float _timeSpeed; // �ð� ���, 1 = �⺻ �ӵ�

	Camera* _bgCamera; // ��� ī�޶�
	Camera* _camera; // �Ϲ� ī�޶�

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

	// ī�޶� ���� �Լ�
	Camera* getBgCamera() const { return _bgCamera; }
	Camera* getCamera() const { return _camera; }

	// UI ���� �Լ�



};

