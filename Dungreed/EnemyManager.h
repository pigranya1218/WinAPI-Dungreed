#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Banshee.h"

class EnemyManager
{
private:
	vector<Enemy*> _vEnemy;		// 에너미 담을 벡터


public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void spawn(Vector2 pos, ENEMY_TYPE enemyType, DIRECTION direction = DIRECTION::RIGHT);
};

