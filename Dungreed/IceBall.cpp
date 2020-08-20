#include "IceBall.h"
#include "stdafx.h"

void IceBall::init()
{
	//악세서리 타입
	_itemCode = 0x03108;
	_iconImg = IMAGE_MANAGER->findImage("IceBall");
	_itemName = L"얼음 덩어리";
	_displayInfos.push_back(L"모험가 주위를 돌며 적을 공격한다");
	_displayText = L"\"싸늘함이 주변을 맴돈다";
	//악세서리 옵션
	_addStat.criticalChance = 1;
	_addStat.defense = 1;
	
	//악세서리 가격
	_price = 600;

	_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
	_radius = 85;
	_fspeed = 10;
	_x = _y = 0;
	_elapsedTime = 0;
	_img = IMAGE_MANAGER->findImage("IceBall0");
	_ani = new Animation;
	_ani->start();
	_setitem = false;
}

void IceBall::release()
{
}

void IceBall::update(Player * player, float const elapsedTime)
{
	_angle -= 3.362f*elapsedTime;
	_ani->frameUpdate(elapsedTime);
	_elapsedTime += elapsedTime;
	_x = cosf(_angle) * _radius;
	_y = -sinf(_angle) * _radius;
	

	if (_elapsedTime > 0.4) // 0.4초마다 공격판정 초기화
	{
		_elapsedTime = 0;
		_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
	}
	
	Vector2 playerPos = player->getPosition();

	FloatCircle* attackCircle;
	attackCircle = new FloatCircle;
	attackCircle->origin = Vector2(playerPos.x + _x, playerPos.y + _y);
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

void IceBall::backRender(Player * player)
{	
	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + _x;
	renderPos.y = renderPos.y + _y;
	_img->setScale(4);
	_ani->init(_img->getWidth(), _img->getHeight(),
	_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(_fspeed);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
	_img->aniRender(CAMERA->getRelativeV2(renderPos), _ani, false);
	Vector2 size = Vector2(_img->getFrameSize().x * 2, _img->getFrameSize().y * 2);
	_crash = rectMakePivot(Vector2(renderPos.x-1, renderPos.y + 19), size, PIVOT::CENTER);
	
	
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_crash));
	

	

}

void IceBall::frontRender(Player * player)
{
}


