#include "MetalPlateCos.h"

void MetalPlateCos::init()
{
	//�̹��� ����
	_idle = IMAGE_MANAGER->findImage("PLAYER_METAL/IDLE");
	_move = IMAGE_MANAGER->findImage("PLAYER_METAL/MOVE");
	_jump = IMAGE_MANAGER->findImage("PLAYER_METAL/JUMP");
	_die = IMAGE_MANAGER->findImage("PLAYER_METAL/DIE");

	//���̽� ���� ����
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

