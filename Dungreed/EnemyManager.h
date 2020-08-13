#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include "Banshee.h"
#include "BatRed.h"
#include "BatIce.h"
#include "BatNormal.h"
#include "BatGiantRed.h"
#include "SkelBigIce.h"
#include "SkelBigNormal.h"
#include "SkelMagicianIce.h"
#include "SkelSmallBow.h"
#include "Minotaurs.h"
#include "Ovibos.h"

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

	// 에너미 관련 함수
	void spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, DIRECTION direction = DIRECTION::LEFT);
	void moveEnemy(GameObject* object, const Vector2 moveDir);
	bool detectPlayer(GameObject* object, const float distance);
	//void fireEnemy(Projectile* projectile);

	// 플레이어 관련 함수
	Vector2 getPlayerPos();

	void setStage(Stage* stage) { _stage = stage; }
};