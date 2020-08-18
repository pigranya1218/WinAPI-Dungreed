#pragma once
#include "Enemy.h"
#include "Projectile.h"
#include "Banshee.h"
#include "BatBomb.h"
#include "BatRed.h"
#include "BatIce.h"
#include "BatNormal.h"
#include "BatGiantRed.h"
#include "BatGiantNormal.h"
#include "SkelBigIce.h"
#include "SkelBigNormal.h"
#include "SkelMagicianIce.h"
#include "SkelDog.h"
#include "SkelSmallBow.h"
#include "SkelSmallDagger.h"
#include "SkelSmallGsword.h"
#include "Minotaurs.h"
#include "Ovibos.h"
#include "Ghost.h"
#include "Niflheim.h"
#include "Belial.h"

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
	void spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, DIRECTION direction = DIRECTION::LEFT);					// ���ʹ� ��ȯ
	void moveEnemy(GameObject* object, const Vector2 moveDir, bool collisionGround = 1, bool collisionPlatForm = 1);	// ���ʹ� �̵�
	bool detectPlayer(GameObject* object, const float distance);														// ���ʹ� �÷��̾� ����
	void fireEnemy(Projectile* projectile, AttackInfo* attackInfo);														// ���ʹ� �Ҹ�

	// �÷��̾� ���� �Լ�
	Vector2 getPlayerPos();

	// �ǰ� üũ ���� �Լ�
	bool isHit(FloatRect* rc, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile, bool isOnceCollision);

	void setStage(Stage* stage) { _stage = stage; }

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
};