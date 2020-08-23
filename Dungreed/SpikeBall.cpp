#include "SpikeBall.h"
#include "stdafx.h"

void SpikeBall::init()
{
	//악세서리 타입
	_itemCode = 0x0310B;
	_img = IMAGE_MANAGER->findImage("SpikeBall");
	_iconImg = IMAGE_MANAGER->findImage("SpikeBall");
	
	//악세서리 옵션
	_addStat.criticalChance = 1;
	_addStat.defense = 1;

	_itemName = L"뾰족 공";
	_displayInfos.push_back(L"모험가 주위를 돌며 적을 공격");
	_displayText = L"\"모험가의 주위를 돌면서 적들을 혼내준다.\"";
	_x = _y = 0;
	_elapsedTime = 0;
	//악세서리 가격
	_price = 600;

	_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
}

void SpikeBall::release()
{
}

void SpikeBall::update(Player* player, float const elapsedTime)
{
	_angle += 2.233f * elapsedTime;
	_elapsedTime += elapsedTime;
	if (_angle > PI2) 
	{
		_angle -= PI2;
	}
	if (_elapsedTime > 0.4) // 0.4초마다 공격판정 초기화
	{
		_elapsedTime = 0;
		_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
	}

	_x = cosf(_angle) * 110;
	_y = -sinf(_angle) * 110;
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

void SpikeBall::frontRender(Player* player)
{
}

void SpikeBall::backRender(Player* player)
{
	Vector2 renderPos = player->getPosition();
	renderPos.x = renderPos.x + _x;
	renderPos.y = renderPos.y + _y;
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(renderPos), false);
	Vector2 size = Vector2(_img->getFrameSize().x * 4, _img->getFrameSize().y * 4);
	
}
