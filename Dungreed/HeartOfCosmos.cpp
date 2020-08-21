#include "HeartOfCosmos.h"
#include "AccProjectile.h"
void HeartOfCosmos::init()
{
	_itemCode = 0x03307;
	_iconImg = IMAGE_MANAGER->findImage("HeartOfCosmos");
	_itemName = L"우주의 심장";
	_displayInfos.push_back(L"대쉬한 자리에 에너지체를 남김");
	_displayText = L"\"우주를 정복할 수 있는 힘을 가질 수 있을까?' 라는 물음에서 시작된 결정체""\"";	
	
	_price = 4300;
	_img = IMAGE_MANAGER->findImage("HeartOfCosmos0");	

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, false);
	_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
}

void HeartOfCosmos::release()
{
	if (!_ani->isPlay())
	{
		_ani->release();
		
	}
	
}

void HeartOfCosmos::update(Player * player, float const elapsedTime)
{
	if (_ani->isPlay()) {
		_elapsedTime += elapsedTime;
		if (_elapsedTime > 0.4) // 0.4초마다 공격판정 초기화
		{
			_elapsedTime = 0;
			_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
		}

		FloatCircle* attackCircle;
		attackCircle = new FloatCircle;
		attackCircle->origin = Vector2(_renderPos.x, _renderPos.y);
		attackCircle->size = 40;
		attackCircle->startRadian = 0;
		attackCircle->endRadian = PI2;

		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		attackInfo->attackID = TTYONE_UTIL::getHash(_attackCode);
		attackInfo->madeByWeapon = false;
		attackInfo->critical = 0;
		attackInfo->criticalDamage = 0;
		attackInfo->minDamage = 5;
		attackInfo->maxDamage = 10;
		attackInfo->knockBack = 5;

		player->attack(attackCircle, attackInfo);
		delete attackCircle;
		delete attackInfo;
	}

	
	_ani->frameUpdate(elapsedTime);
}

void HeartOfCosmos::backRender(Player * player)
{
	if (_ani->isPlay())
	{
		_img->setScale(4);
		_img->aniRender(CAMERA->getRelativeV2(_renderPos), _ani, false); 
	}	

}

void HeartOfCosmos::frontRender(Player * player)
{
}


void HeartOfCosmos::dash(Player * player)
{
	_playerpos = player->getPosition();
	_renderPos = _playerpos;
	_ani->start();
	/*
	AccProjectile* projectile = new AccProjectile;
	projectile->setPosition(_renderPos);	
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("HeartOfCosmos0", "HeartOfCosmosF", 1, Vector2(200, 200), Vector2(330, 300), Vector2(0, 0), 1.3, 0, true, false, 15, false, false, false, false);
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->madeByWeapon = false;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->maxDamage = 5;
	attackInfo->minDamage = 3;
	player->attack(projectile, attackInfo);	
	*/

	

}


