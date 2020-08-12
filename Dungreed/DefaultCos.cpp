#include "DefaultCos.h"

void DefaultCos::init()
{
	//이미지 설정
	_idle = IMAGE_MANAGER->findImage("PLAYER/IDLE");
	_move = IMAGE_MANAGER->findImage("PLAYER/RUN");
	_jump = IMAGE_MANAGER->findImage("PLAYER/JUMP");
	_die = IMAGE_MANAGER->findImage("PLAYER/DIE");

	//현재 재생할 이미지
	_img = _idle;
	_ani = new Animation;
	setAni(PLAYER_ANIMATION::IDLE);
	_aniState = PLAYER_ANIMATION::IDLE;
	
	//베이스 스탯
	_baseStat.maxHp = 80;
	_baseStat.maxJumpCount = 1;
	_baseStat.maxDashCount = 5;
	_baseStat.dashCoolTime = 1.5f;
	_baseStat.maxSatiety = 100;
	_baseStat.power = 5;
	_baseStat.damage = 0; //0 ~ 4
	_baseStat.trueDamage = 0;
	_baseStat.criticalChance = 2;
	_baseStat.criticalDamage = 1; // + 100%
	_baseStat.toughness = 0;
	_baseStat.defense = 0;
	_baseStat.block = 0;
	_baseStat.evasion = 0;
	_baseStat.attackSpeed = 0;
	_baseStat.reloadSpeed = 0; // --
	_baseStat.moveSpeed = 350;
	_baseStat.dashXPower = 2400;
	_baseStat.dashYPower = 1700;
	_baseStat.jumpPower = 1700;
	_baseStat.xGravity = 10000;
	_baseStat.yGravity = 5000;
}

void DefaultCos::release()
{
}

void DefaultCos::update(float elaspedTime)
{
	_ani->frameUpdate(elaspedTime);
}

void DefaultCos::render(Vector2 pos, DIRECTION dir, PLAYER_ANIMATION state)
{
	if(state != PLAYER_ANIMATION::DEFAULT) _img->aniRender(pos, _ani, false);
	else _img->render(pos, false);
}

void DefaultCos::setAni(PLAYER_ANIMATION aniState)
{
	switch (aniState)
	{
	case PLAYER_ANIMATION::IDLE:
	{
		_ani->stop();
		_img = _idle;
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
		_ani->start();
	}
	break;
	case PLAYER_ANIMATION::MOVE:
	{
		_ani->stop();
		_img = _move;
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
		_ani->start();
	}
	break;
	default:
	{
		_img = _jump;
	}
	break;
	}
}

PlayerStat DefaultCos::getBaseStat()
{
	return PlayerStat();
}
