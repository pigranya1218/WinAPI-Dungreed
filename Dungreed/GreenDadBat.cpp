#include "GreenDadBat.h"
#include "stdafx.h"
#include "NormalProjectile.h"

void GreenDadBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::HIGH;
	_iconImg = IMAGE_MANAGER->findImage("GreenDadBat");

	_price = 3500;

	batPos.x = WINSIZEX / 2;
	batPos.y = WINSIZEY / 2;
	
	_img = IMAGE_MANAGER->findImage("GreenDadBatF");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(9);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);

	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
	_drawEffect = false;
}

void GreenDadBat::release()
{
}

void GreenDadBat::update(Player * player, float const elapsedTime)
{
	if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	else if (_currReloadDelay > 0) // 재장전 중
	{
		_currReloadDelay = max(0, _currReloadDelay - elapsedTime);
		if (_currReloadDelay == 0) // 장전이 끝난 경우
		{
			_currBullet = _maxBullet;
		}
	}
	if (_ptMouse.x < renderPos.x)
	{
		_direction = DIRECTION::LEFT;

	}
	else
	{
		_direction = DIRECTION::RIGHT;

	}
	_ani->frameUpdate(elapsedTime);
	
}

void GreenDadBat::backRender(Player * player)
{
	renderPos = player->getPosition();
	if (batPos.x > renderPos.x - 70)
	{
		batPos.x -= 6;
	}
	else if (batPos.x <= renderPos.x -90)
	{
		batPos.x += 6;
	}
	if (batPos.y > renderPos.y + 5 && batPos.y > renderPos.y)
	{
		batPos.y -= 7;
	}
	else if (batPos.y < renderPos.y - 5 )
	{
		batPos.y += 8;
	}
	_img->setScale(4);
	_img->aniRender(Vector2(batPos), _ani, _direction == DIRECTION::LEFT);


}

void GreenDadBat::frontRender(Player * player)
{
}

void GreenDadBat::displayInfo()
{
}

void GreenDadBat::attack(Player * player)
{
	if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	if (_currBullet == 0) // 총알이 없다면
	{
		if (_currReloadDelay == 0) // 재장전 중이 아니라면
		{
			_currReloadDelay = _baseReloadDelay; // 재장전 함
		}
		return;
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = batPos;

	// 손으로부터 마우스 에임까지의 각도
	float angleRadian = atan2f(-(_ptMouse.y - batPos.y), (_ptMouse.x - batPos.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	NormalProjectile* projectile = new NormalProjectile;
	Vector2 shootPos = pos;
	float length = _img->getWidth() * 0.1f; // 길이만큼
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(170, 170));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 13, true, true, 20, false, "BabyBatBulletFx", Vector2(170, 170));
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // 공격 쿨타임 설정
	_currBullet -= 1; // 탄환 1 줄임
	_drawEffect = true; // 이펙트 그리기
}

void GreenDadBat::attack(FloatRect * rect, AttackInfo * info)
{
}

void GreenDadBat::attack(FloatCircle * circle, AttackInfo * info)
{
}

void GreenDadBat::attack(Projectile * projectile, AttackInfo * info)
{
}

void GreenDadBat::getHit(Vector2 const position)
{
}

PlayerStat GreenDadBat::equip()
{
	return PlayerStat();
}
