#include "RedLotusCos.h"

void RedLotusCos::init()
{
	//코스튬 이름 설정
	_costumeName = "RED_LOTUS";

	//코스튬 설명창에 보여줄 내용들
	_costumeTitle = L"홍련";
	_costumeSummary = L"저 너머로...개화하고 싶지 않은가, 그대?";
	_costumeDetails = L"표식: 적을 공격하면 위력을 6올려주는 표식을 남깁니다. (최대 10개)";

	_ani = new Animation;

	//현재 재생할 이미지
	setSprite(PLAYER_STATE::IDLE, true);

	//변동 스탯
	_differStat.maxHp = -15;
	_differStat.evasion = -5;

	//베이스 스탯
	_baseStat.maxHp = 80;
	_baseStat.maxJumpCount = 1;
	_baseStat.maxDashCount = 5;
	_baseStat.dashCoolTime = 1.5f;
	_baseStat.maxSatiety = 100;
	_baseStat.power = 5;
	_baseStat.minDamage = 0; //0 ~ 4
	_baseStat.maxDamage = 0; //0 ~ 4
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
	_baseStat.dashXPower = 1600;
	_baseStat.dashYPower = 1400;
	_baseStat.jumpPower = 1400;
	_baseStat.xGravity = 4000;
	_baseStat.yGravity = 4000;
}

void RedLotusCos::release()
{
	_ani->release();
	delete _ani;
}

void RedLotusCos::update(float elaspedTime)
{
	if (_ani->isPlay())
	{
		_ani->frameUpdate(elaspedTime);
	}
}

void RedLotusCos::render(Vector2 pos, DIRECTION dir)
{
	// 확대
	_img->setScale(4);

	// 상태에 따른 애니메이션 사용 여부 
	switch (_imgState)
	{
	case PLAYER_STATE::IDLE:
	case PLAYER_STATE::MOVE:
	{
		_img->aniRender(pos, _ani, (dir == DIRECTION::LEFT));
	}
	break;
	case PLAYER_STATE::JUMP:
	case PLAYER_STATE::DIE:
	{
		_img->render(pos, (dir == DIRECTION::LEFT));
	}
	break;
	}
}

void RedLotusCos::setSprite(PLAYER_STATE state, bool isForced)
{
	if (_imgState == state && !isForced) return;

	switch (state)
	{
	case PLAYER_STATE::IDLE:
	{
		_imgState = PLAYER_STATE::IDLE;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/IDLE");
		_ani->stop();
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setDefPlayFrame(false, true);
		_ani->start();
	}
	break;
	case PLAYER_STATE::MOVE:
	{
		_imgState = PLAYER_STATE::MOVE;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/MOVE");
		_ani->stop();
		_ani->init(_img->getWidth(), _img->getHeight(),
			_img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setFPS(10);
		_ani->setDefPlayFrame(false, true);
		_ani->start();
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		_imgState = PLAYER_STATE::JUMP;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/JUMP");
		_ani->stop();
	}
	break;
	case PLAYER_STATE::DIE:
	{
		_imgState = PLAYER_STATE::DIE;

		_img = IMAGE_MANAGER->findImage("COSTUME/" + _costumeName + "/DIE");
		_ani->stop();
	}
	break;
	}
}
