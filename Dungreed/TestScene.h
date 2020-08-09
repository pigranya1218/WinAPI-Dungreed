#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "EnemyManager.h"


struct tagTestPlayer
{
	
	float x, y;
	
	FloatRect rc;


};

class TestScene : public GameNode
{

	

private:

	float playerx, playery;
	float angle;
	float speed;
	float x, y;
	FloatRect RC[2];

	EnemyManager* _em;




public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
	
};

