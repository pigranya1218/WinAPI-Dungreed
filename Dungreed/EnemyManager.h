#pragma once
#include "Enemy.h"
#include "Banshee.h"
#include "BatRed.h"
#include "BatIce.h"
#include "BatNormal.h"
#include "SkelBigIce.h"
#include "SkelBigNormal.h"
#include "SkelMagicianIce.h"
#include "SkelSmallBow.h"

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

	//
	void spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, DIRECTION direction = DIRECTION::LEFT);
	void moveEnemy(GameObject* object, const Vector2 moveDir);

	// 플레이어 관련 함수
	Vector2 getPlayerPos();

	// 에너미 관련 함수
	bool detectPlayer(GameObject* object, const float distance);

	void setStage(Stage* stage) { _stage = stage; }
};

