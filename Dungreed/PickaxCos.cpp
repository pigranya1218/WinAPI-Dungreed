#include "PickaxCos.h"
#include "PlayerStat.h"

void PickaxCos::init()
{
	// 이미지 설정
	_idle = IMAGE_MANAGER->findImage("PLAYER_PICKAX/IDLE");
	_move = IMAGE_MANAGER->findImage("PLAYER_PICKAX/RUN");
	_jump = IMAGE_MANAGER->findImage("PLAYER_PICKAX/JUMP");
	_die = IMAGE_MANAGER->findImage("PLAYER_PICKAX/DIE");

	// 베이스 스텟 설정
	_baseStat.attackSpeed = 10;
}

void PickaxCos::release()
{
}

void PickaxCos::update(float elaspedTime)
{
}

void PickaxCos::render(Vector2 pos, DIRECTION dir, PLAYER_ANIMATION state)
{
}

void PickaxCos::setAni(PLAYER_ANIMATION aniState)
{
}

PlayerStat PickaxCos::getBaseStat()
{
	return PlayerStat();
}
