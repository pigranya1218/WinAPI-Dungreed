#include "Voluspa.h"
#include "stdafx.h"
#include "Stage.h"

void Voluspa::init()
{

	//악세서리 타입
	_itemCode = 0x0330C;
	_img = IMAGE_MANAGER->findImage("Voluspa0");
	_iconImg = IMAGE_MANAGER->findImage("Voluspa");
	//악세서리 옵션

	_itemName = L"볼루스파";
	_displayInfos.push_back(L"적을 자동으로 노리는  얼음창 소환");
	_displayText = L"\"그대 아직도 깨달음을 원하는가? 그리고 무엇을 알려는가?\"";
	//악세서리 가격
	_price = 4300;
	_currAttackDelay = 1.7f;
	_currStopDelay = 1.7f;
	_location.x = 0;
	_location.y = 0;
	
	_renderPos.x = -300;
	_renderPos.y = WINSIZEY/2;
	_Opposition = false;
	_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
}

void Voluspa::release()
{
}

void Voluspa::update(Player * player, float const elapsedTime)
{	
	Vector2 enemypos = player->getEnemyPos(Vector2());
	_elapsedTime += elapsedTime;
	_location.x = 2500* elapsedTime;

		
	if (_renderPos.x > WINSIZEX+300 )
	{
		if (_currStopDelay > 0) // 공격 딜레이 대기 중
		{
			_currStopDelay = max(0, _currStopDelay - elapsedTime);		}
		
		if (_currStopDelay == 0 ) {
			_renderPos.y = CAMERA->getAbsoluteY(enemypos.y);			
			_currAttackDelay = 1.7f;
			_Opposition = true;
		}
	}
	if (_renderPos.x < -300 )
	{
		if (_currAttackDelay > 0) // 공격 딜레이 대기 중
		{
			_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
		}
		
		if (_currAttackDelay == 0 ) {
			_renderPos.y = CAMERA->getAbsoluteY(enemypos.y);			
			_currStopDelay = 1.7f;
			_Opposition = false;
		}
	}
	if (_Opposition)
	{
		_renderPos.x -= _location.x;
	}
	else
	{
		_renderPos.x += _location.x;
	}
	if (_elapsedTime > 0.6) // 0.4초마다 공격판정 초기화
	{
		_elapsedTime = 0;
		_attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함
	}	
	

	FloatCircle* attackCircle;
	attackCircle = new FloatCircle;
	attackCircle->origin = Vector2(_renderPos.x , _renderPos.y);
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

void Voluspa::backRender(Player * player)
{

	_img->setScale(3);	
	if (_Opposition)
	{
		_img->render(CAMERA->getRelativeV2(_renderPos), true);
	}
	else
	{
		_img->render(CAMERA->getRelativeV2(_renderPos), false);
	}

	
}

void Voluspa::frontRender(Player * player)
{
}


