#include "stdafx.h"
#include "BigPaintBlush.h"
void BigPaintBlush::init()
{
	_img = IMAGE_MANAGER->findImage("BigPaintBlush");
	_iconImg = IMAGE_MANAGER->findImage("BigPaintBlush");

	_width = _img->getFrameSize().x;
	_height = _img->getFrameSize().y;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(20);
	_ani->start();
	_ani->isPlay();
	_itemName = L"서예용 붓";
	_displayText = L"\"아름답게 글자를 쓰는 것이 귀족들 사이에서 유행이라고 한다\"";
	_itemCode = 0x01103;

	_price = 1200;

	// 기본 보조옵션
	
	_addStat.minDamage = 2;
	_addStat.maxDamage = 5;
	_addStat.attackSpeed = 0.4;
	_handSize = Vector2(5, 5);

	
	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
	_oneAttack = true;
	_angleOffset = 15;
}

void BigPaintBlush::release()
{

	

}



void BigPaintBlush::update(Player* player, float const elapsedTime)
{

	


	for (int i = 0; i < _VtagAttack.size();)
	{
		_VtagAttack[i]._hitDelay += elapsedTime;
		if (_VtagAttack[i]._hitDelay >= 0.4)
		{
			_VtagAttack[i]._hitDelay = 0;
			_VtagAttack[i]._count++;

			delete _VtagAttack[i]._attackInfo;
			string attackCode = to_string(_itemCode) + to_string(_VtagAttack[i]._count) + to_string(TIME_MANAGER->getWorldTime());
			AttackInfo* attackInfo = new AttackInfo;
			attackInfo->team = OBJECT_TEAM::PLAYER;
			attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
			attackInfo->critical = 0;
			attackInfo->criticalDamage = 0;
			attackInfo->minDamage = _addStat.minDamage;
			attackInfo->maxDamage = _addStat.maxDamage;
			attackInfo->knockBack = 15;

			_VtagAttack[i]._attackInfo = attackInfo;
		}
		if (_VtagAttack[i]._count >= 5)
		{
			delete _VtagAttack[i]._attackCircle;
			delete _VtagAttack[i]._attackInfo;
			_VtagAttack.erase(_VtagAttack.begin() + i);
		}
		else
		{
			player->attack(_VtagAttack[i]._attackCircle, _VtagAttack[i]._attackInfo);
			i++;
		}
	}

	Vector2 pos = player->getPosition();
	float time = elapsedTime-1;
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);
	if (degree > 360)
	{
		degree -= 360;
	}

	if (_drawEffect)
	{
		_drawEffect = false;
		Vector2 effectPos = pos;
		float length = _img->getWidth() * 4 * 1.0;
		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;
		EFFECT_MANAGER->play("EFFECT_PAINTSWING", effectPos, Vector2(130, 200), degree);
	}

	if (_currAttackDelay == 0) return;

	if (FLOAT_EQUAL(_currAttackDelay, _addStat.attackSpeed))
	{

		if (_oneAttack)
		{
			_angleOffset += 155;
			_oneAttack = false;

		}
		else
		{
			_angleOffset -= 155;
			_oneAttack = true;
		}
	}
	float ratio = elapsedTime / (_addStat.attackSpeed * 0.15);
	if (_reverseMove)
	{
	}
	else
	{
		if (_currAttackDelay <= _addStat.attackSpeed * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
		}
	}

	
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);

	
}

void BigPaintBlush::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	if (_oneAttack)
	{
		
		originPos.x += ((isLeft) ? -20 : 20);



		

		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x - pos.x))) * (180 / PI);
		float degreeOffsetangle = degree + 90;



		if (degree > 360)
		{
			degree -= 360;
		}
		if (degreeOffsetangle > 360)
		{
			degreeOffsetangle -= 360;
		}
		
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) 
		{

			renderPosWeapon.x -= 31 - (cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosWeapon.y += 20 + (sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
			renderPosHand.x -= (-cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosHand.y += 20 + (sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		}
		else
		{
			renderPosWeapon.x += 31 + (-cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4));
			renderPosWeapon.y += 20 + (-sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
			renderPosHand.x += -cosf(degreeOffsetangle * (PI / 180))*-(_img->getWidth() * 0.4f * 4);
			renderPosHand.y += 20 + (-sinf(degreeOffsetangle * (PI / 180))) * (_img->getHeight() * 0.8f * 4);
		}
		float renderDegree = degreeOffsetangle;

		if (isLeft) 
		{
			renderDegree = 360 - degreeOffsetangle;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		
		renderPosWeapon.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y)); 
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			
		renderPosHand.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y));	

		_img->setScale(4); 
		_img->setAngle(renderDegree + _angleOffset); 
		if (isLeft)
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); 
		}
		else
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight())); 

		}
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);
		Vector2 last = renderPosHand;

		if (isLeft) // 왼쪽을 보고 있음
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(last)); 
		}
		else
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (renderDegree + _angleOffset), CAMERA->getRelativeV2(last));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (renderDegree + _angleOffset), CAMERA->getRelativeV2(last)); 
		}
		
	}



}

void BigPaintBlush::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 originPos = player->getPosition();
	Vector2 pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPos = Vector2(originPos.x + 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, _handSize, PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1, 2.f);
	}
	else
	{
		Vector2 renderPos = Vector2(originPos.x - 25, originPos.y + 20);

		_hand = rectMakePivot(renderPos, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1);
		D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1, 2.f);
	}
	if (!_oneAttack)
	{
		
		originPos.x += ((isLeft) ? -40 : 20);

		

		float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - pos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - pos.x)) * (180 / PI);
		float degreeOffsetangle = degree + 90;

		if (degree > 360)
		{
			degree -= 360;
		}
		if (degreeOffsetangle > 360)
		{
			degreeOffsetangle -= 360;
		}
		
		Vector2 renderPosHand = originPos;
		Vector2 renderPosWeapon = originPos;

		if (isLeft) 
		{

			renderPosWeapon.x += -2 + (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x += 52 + (-cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) - 23;
			renderPosHand.y += 5 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		else
		{
			renderPosWeapon.x -= -12 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4));
			renderPosWeapon.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
			renderPosHand.x -= 42 + (cosf(degreeOffsetangle * (PI / 180)) * -(_img->getWidth()  * 0.1f * 4)) - 23;
			renderPosHand.y += 25 + (-sinf(degreeOffsetangle * (PI / 180)) *  (_img->getHeight() * 0.4f * 4));
		}
		float renderDegree = degreeOffsetangle;

		if (isLeft) 
		{
			renderDegree = 360 - degreeOffsetangle;
			if (renderDegree < 0) renderDegree += 360;
		}

		renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));		
		renderPosWeapon.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y)); 
		renderPosHand.x += ((isLeft) ? (_attackMove.x) : (-_attackMove.x));			
		renderPosHand.y += ((degreeOffsetangle >= 180) ? (_attackMove.y) : (-_attackMove.y));	
		_img->setScale(4); 
		_img->setAngle(renderDegree + _angleOffset);
		if (isLeft)
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight()));
		}
		else
		{
			_img->setAnglePos(Vector2(0.2f * _img->getWidth(), 0.5f * _img->getHeight()));

		}
		_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);

		_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

		if (isLeft)
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, -(renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand)); 
		}
		else
		{
			D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(_hand), 210, 188, 181, 1, (renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
			D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(_hand), 40, 36, 58, 1.f, 2.f, (renderDegree + _angleOffset), CAMERA->getRelativeV2(renderPosHand));
		}
		
	}
}


void BigPaintBlush::attack(Player* player)
{
	if (_currAttackDelay > 0) return;
			
	CAMERA->pushShakeEvent(10,0.1f);
	   		_reverseMove = false;
	_currAttackDelay = _addStat.attackSpeed;
	
	Vector2 originPos = player->getPosition();
	originPos.x += ((player->getDirection() == DIRECTION::LEFT) ? -15 : 15);
	originPos.y += 10;
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); 

	SOUND_MANAGER->stop("SOUND_swing1");
	SOUND_MANAGER->play("SOUND_swing1", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

	FloatCircle* attackCircle = new FloatCircle;
	attackCircle->origin = originPos;
	attackCircle->size = 150;
	attackCircle->startRadian = attackRadian - PI * 0.28;
	attackCircle->endRadian = attackRadian + PI * 0.28;

	_attackDebug = FloatCircle(originPos, 150, attackRadian - PI * 0.37, attackRadian + PI * 0.37); 
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 15;
	
	tagAttack attack;
	attack._attackCircle = attackCircle;
	attack._attackInfo = attackInfo;
	attack._hitDelay = 0;
	attack._count = 0;
	_VtagAttack.push_back(attack);

	


}

void BigPaintBlush::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
