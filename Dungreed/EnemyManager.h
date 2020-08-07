#pragma once
#include "GameNode.h"
#include "Enemy.h"




class EnemyManager
{
private:
	vector<Enemy*> _vEnemy;		// ���ʹ� ���� ����


public:
	EnemyManager();
	~EnemyManager();

	void init();
	void release();
	void update();
	void render();

	void spawn(ENEMY_TYPE enemyType, Vector2 pos);
};

