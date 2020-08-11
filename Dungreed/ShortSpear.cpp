#include "stdafx.h"
#include "ShortSpear.h"

void ShortSpear::init()
{
	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("ShortSpear");
	_price = 600;

	// 기본 보조옵션
	_addStat.dashDamage = 20;




	// private 변수 설정
	_attackMove = Vector2(0, 0);
	_minDamage = 7;
	_maxDamage = 10;
	_baseAttackDelay = 0.5;
	_currAttackDelay = 0;
	_reverseMove = false;
}

void ShortSpear::release()
{
}

void ShortSpear::update(float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_baseAttackDelay * 0.08);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.88)
		{
			_reverseMove = true;
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSpear::backRender(Vector2 pos, float angle)
{
}

void ShortSpear::frontRender(Vector2 pos, float angle)
{
	Vector2 renderPos = pos;
	bool isLeft = false;
	if (angle >= 90 && angle <= 270) // 왼쪽을 보고 있음
	{
		isLeft = true;
		angle = fmod((180 - angle) + 360, 360);
	}
	
	renderPos.x += ((isLeft)?(-10 - _attackMove.x):(10 + _attackMove.x));
	renderPos.y += 15 + ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(angle);
	_img->setAnglePos(Vector2(_img->getWidth() * 0.3f, _img->getHeight() * 0.5f));
	_img->render(renderPos, isLeft);
}

void ShortSpear::displayInfo()
{
}

void ShortSpear::attack(Vector2 const position, float const angle)
{
	if (_currAttackDelay > 0) return;

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void ShortSpear::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void ShortSpear::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void ShortSpear::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void ShortSpear::getHit(Vector2 const position)
{
}

PlayerStat ShortSpear::equip()
{
	return PlayerStat();
}
