#include "stdafx.h"
#include "CosmosSword.h"
#include "NormalProjectile.h"

void CosmosSword::init()
{
	_img = IMAGE_MANAGER->findImage("CosmosSword");
	_iconImg = IMAGE_MANAGER->findImage("CosmosSwordIcon");

	_width = _img->getFrameSize().x;
	_height = _img->getFrameSize().y;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();

	_itemName = L"우주검";
	_displayText = L"\"이 검이 내뿜는 우주의 신비한 빛\"";
	_itemCode = 0x02400; // 양손 전설

	_price = 600;

	// 기본 보조옵션
	
	_addStat.minDamage = 15;
	_addStat.maxDamage = 25;
	_addStat.attackSpeed = 0.4;

	_handSize = Vector2(5, 5);
	

	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 0;

}

void CosmosSword::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void CosmosSword::update(Player* player, float const elapsedTime)
{
	_ani->frameUpdate(elapsedTime);

	if (_currAttackDelay == 0) return;


	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);

}

void CosmosSword::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (_oneAttack)
	{
		// 회전축 중점
		originPos.x += ((isLeft) ? -15 : 15); // 바라보는 방향의 어깨
		originPos.y += 5;

		// 회전축으로부터 마우스까지의 각도값
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

		float handDegree = degree + ((isLeft) ? -110 : 110);

		// 좌우 대칭을 위한 계산
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}

		// 손의 위치 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (_width * 0.1 * 4);
		// 무기 위치
		renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft)?(-_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4): (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;

		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // 이미지 각도 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다

		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = originPos; // 회전축의 위치로부터
			float length = _width * 4 * 1; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_COSMOSSWING", effectPos, Vector2(250, 300), degree);
		}
	}
}

void CosmosSword::frontRender(Player* player)
{

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();

	if (!_oneAttack)
	{
		// 회전축 중점
		originPos.x += ((isLeft) ? -15 : 15); // 바라보는 방향의 어깨
		originPos.y += 10;

		// 회전축으로부터 마우스까지의 각도값
		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x)) * (180 / PI);

		float handDegree = degree + ((isLeft) ? (-110 - _angleOffset) : (110 + _angleOffset));

		// 좌우 대칭을 위한 계산
		float weaponDegree = handDegree;
		if (isLeft)
		{
			weaponDegree = 180 - weaponDegree;
		}

		// 손의 위치 
		Vector2 renderPosHand = originPos;
		renderPosHand.x += (_width * 0.1 * 4);
		// 무기 위치
		renderPosWeapon = originPos;
		renderPosWeapon.x += (isLeft) ? (-_width * 0.35 * 4 - cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4) : (_width * 0.35 * 4 + cosf(weaponDegree * (PI / 180)) * _width * 0.15 * 4);
		renderPosWeapon.y += -sinf(weaponDegree * (PI / 180)) * _width * 0.15 * 4;

		_img->setScale(4); // 이미지 크기 
		_img->setAngle(weaponDegree /*+ _angleOffset*/); // 이미지 각도 
		_img->setAnglePos(Vector2(0.15f * _width, 0.5f * _height)); // 이미지 회전시킬 중점
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);// 그린다

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다
		Vector2 renderPosHand2 = renderPosHand;
		renderPosHand2.x += _width * 0.06f * 4;
		FloatRect hand2 = FloatRect(renderPosHand2, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(hand2), 210, 188, 181, 1, (handDegree), CAMERA->getRelativeV2(originPos));
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(hand2), 40, 36, 58, 1.f, 2.f, (handDegree), CAMERA->getRelativeV2(originPos)); // 손의 렉트를 그린다

		if (_drawEffect) // 이펙트를 그린다
		{
			_drawEffect = false;
			Vector2 effectPos = originPos; // 회전축의 위치로부터
			float length = _width * 4 * 1; // 무기 길이만큼
			effectPos.x += cosf(degree * (PI / 180)) * length;
			effectPos.y += -sinf(degree * (PI / 180)) * length;
			EFFECT_MANAGER->play("EFFECT_COSMOSSWING", effectPos, Vector2(250, 300), degree);
		}
	}

	_attackDebug.render(true);
}



void CosmosSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	if (_oneAttack)
	{
		_angleOffset += 95;
	}
	else
	{
		_angleOffset -= 95;
	}
	_oneAttack = !_oneAttack;
	
	_drawEffect = true;
	_currAttackDelay = _addStat.attackSpeed;

	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15); // 바라보는 방향의 어깨
	originPos.y += 10;
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0) 
	{ 
		attackRadian += PI2;
	}
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	FloatCircle* attackCircle = new FloatCircle;
	attackCircle->origin = originPos;
	attackCircle->size = 240;
	attackCircle->startRadian = attackRadian - PI * 0.28;
	attackCircle->endRadian = attackRadian + PI * 0.28;

	_attackDebug = FloatCircle(originPos, 240, attackRadian - PI * 0.28, attackRadian + PI * 0.28); // forDEBUG

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage= _addStat.minDamage;
	attackInfo->maxDamage= _addStat.maxDamage;
	attackInfo->knockBack = 15;

	//==========================================================
	float radian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x))/* * (180 / PI)*/;
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	
	Vector2 shootPos = renderPosWeapon;
	float length = _img->getFrameSize().x * 0.6f * 4; // 무기 길이만큼
	shootPos.x += cosf(radian) * length;
	shootPos.y += -sinf(radian) * length;
	
	NormalProjectile* projectile;
	projectile = new NormalProjectile;
	projectile->setPosition(shootPos);	
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("CosmosSwordFx", "EFFECT_COSMOSSLASH", Vector2(250, 300), Vector2(50, 50), Vector2(20, 250), Vector2(30 * 50, 30 * 50), 3, radian, true, true, 10, true, false, false, false, false);

	AttackInfo* attackInfo2 = new AttackInfo;
	attackInfo2->team = OBJECT_TEAM::PLAYER;
	attackInfo2->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo2->critical = 0;
	attackInfo2->criticalDamage = 0;
	attackInfo2->minDamage = _addStat.minDamage;
	attackInfo2->maxDamage = _addStat.maxDamage;
	attackInfo2->knockBack = 15;
	//==============================================================================================================================================================
	player->attack(attackCircle, attackInfo);
	player->attack(projectile, attackInfo2);

	delete attackCircle;
	delete attackInfo;
}



void CosmosSword::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
