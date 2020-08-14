#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include "Banshee.h"
#include "BatRed.h"
#include "BatIce.h"
#include "BatNormal.h"
#include "BatGiantRed.h"
#include "BatGiantNormal.h"
#include "SkelBigIce.h"
#include "SkelBigNormal.h"
#include "SkelMagicianIce.h"
#include "SkelSmallBow.h"
#include "Minotaurs.h"
#include "Ovibos.h"
#include "Ghost.h"

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

	// ���ʹ� ���� �Լ�
	void spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, DIRECTION direction = DIRECTION::LEFT);	// ���ʹ� ��ȯ
	void moveEnemy(GameObject* object, const Vector2 moveDir);											// ���ʹ� �̵�
	bool detectPlayer(GameObject* object, const float distance);										// ���ʹ� �÷��̾� ����
	void fireEnemy(Projectile* projectile, AttackInfo* attackInfo);										// ���ʹ� �Ҹ�

	// �÷��̾� ���� �Լ�
	Vector2 getPlayerPos();

	void setStage(Stage* stage) { _stage = stage; }
};