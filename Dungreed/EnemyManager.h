#pragma once
#include "Enemy.h"

class Stage;

class EnemyManager
{
private:
	Stage* _stage;
	vector<Enemy*> _enemies;

public:
	void init();
	void release();
	void update(float const timeElapsed);
	void render();

	void spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, DIRECTION direction);

	// 플레이어 관련 함수
	Vector2 getPlayerPos();
};

