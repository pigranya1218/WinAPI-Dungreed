#pragma once
#include "GameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "UIManager.h"

class GameScene : public GameNode
{
private:
	float _timeSpeed; // �ð� ���, 1 = �⺻ �ӵ�

	Camera* _bgCamera; // ��� ī�޶�, �÷��̾��� �����Ӻ��� ���� ȭ�� �̵�
	Camera* _camera; // �Ϲ� ī�޶�, �÷��̾��� �����ӿ� ���� ȭ�� �̵�

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



	// �������� ���� �Լ�

	// ī�޶� ���� �Լ�
	Camera* getBgCamera() const { return _bgCamera; }
	Camera* getCamera() const { return _camera; }

	// UI ���� �Լ�



};

