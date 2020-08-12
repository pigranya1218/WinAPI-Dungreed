#include "MetalPlateCos.h"

void MetalPlateCos::init()
{
	//이미지 설정
	_idle = IMAGE_MANAGER->findImage("PLAYER_METAL/IDLE");
	_move = IMAGE_MANAGER->findImage("PLAYER_METAL/MOVE");
	_jump = IMAGE_MANAGER->findImage("PLAYER_METAL/JUMP");
	_die = IMAGE_MANAGER->findImage("PLAYER_METAL/DIE");

	//베이스 스탯 설정
}

void MetalPlateCos::release()
{
}

void MetalPlateCos::update(float elaspedTime)
{

}

void MetalPlateCos::render(Vector2 pos, DIRECTION dir, PLAYER_ANIMATION state)
{

}

void MetalPlateCos::setAni(PLAYER_ANIMATION aniState)
{
}

PlayerStat MetalPlateCos::getBaseStat()
{
	return PlayerStat();
}

