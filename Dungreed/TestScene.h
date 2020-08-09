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
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용
	
};

