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

	// 에너미 관련 함수
	void spawnEnemy(ENEMY_TYPE enemyType, const Vector2& pos, bool spawnEffect = 0, DIRECTION direction = DIRECTION::LEFT);	// 에너미 소환
	void moveEnemy(GameObject* object, const Vector2 moveDir, bool collisionGround = 1, bool collisionPlatForm = 1);		// 에너미 이동
	bool detectPlayer(GameObject* object, const float distance);															// 에너미 플레이어 감지
	void fireEnemy(Projectile* projectile, AttackInfo* attackInfo);															// 에너미 불릿
	Vector2 getEnemyPos(const Vector2& pos);	// 좌표 기준 가장 가까운 에너미 좌표 반환
	vector<FloatRect> getEnemyRects();
	vector<Vector2> getAllEnemyPos();
	void claerEnemy();	// 생성되어 있는 모든 에너미 삭제

	// 플레이어 관련 함수
	Vector2 getPlayerPos();

	// 공격 관련 함수
	void attack(FloatRect* rc, AttackInfo* info);
	void attack(FloatCircle* circle, AttackInfo* info);

	// 피격 체크 관련 함수
	bool isHit(FloatRect* rc, AttackInfo* info);
	bool isHit(FloatCircle* circle, AttackInfo* info);
	bool isHit(Projectile* projectile, bool isOnceCollision);

	void setStage(Stage* stage) { _stage = stage; }

	void showDamage(DamageInfo info, Vector2 pos);
	void showEnemyHp(float maxHp, float curHp, Vector2 pos);
};