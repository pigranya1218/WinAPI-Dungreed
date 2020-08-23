#pragma once
#include "Enemy.h"

class SkelBigIce : public Enemy
{
private:
	tagAttackInfo	_attack;	// 근접 공격
	tagAttackInfo	_skill;		// 스킬 딜레이용
	tagShootingInfo _shooting;	// 얼음 투사체 발사
	int				_bulletNum;	// 현재 생성한 얼음 투사체 갯수

public:
	void init(const Vector2& pos, DIRECTION direction, bool spawnEffect);
	void release();
	void update(float const timeElapsed);
	void render();

	void setState(ENEMY_STATE state);

	void hitReaction(const Vector2& playerPos, Vector2& moveDir, const float timeElapsed);
};

