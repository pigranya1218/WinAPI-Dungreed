#include "stdafx.h"
#include "ShortSword.h"

void ShortSword::init()
{

	_type = ITEM_TYPE::WEAPON_ONE_HAND;
	_rank = ITEM_RANK::NORMAL;
	_img = IMAGE_MANAGER->findImage("ShortSword");
	_price = 600;


}

void ShortSword::release()
{
}

void ShortSword::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_baseAttackDelay * 0.08);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 30 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 30), _attackMove.x + abs(cosf(_attackAngle) * 30 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 30), _attackMove.y + abs((-sinf(_attackAngle)) * 30 * ratio));

		if (_currAttackDelay <= _baseAttackDelay * 0.88)
		{
			_reverseMove = true;
		}
	}

	// 공격 딜레이 계산
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSword::backRender(Vector2 pos, float angle)
{

}

void ShortSword::frontRender(Vector2 pos, float angle)
{

	Vector2 renderPos = pos;
	bool isLeft = false;
	if (angle >= 90 && angle <= 270) // 왼쪽을 보고 있음
	{
		isLeft = true;
		angle = fmod((180 - angle) + 360, 360);
	}

	renderPos.x += ((isLeft) ? (-10 - _attackMove.x) : (10 + _attackMove.x));
	renderPos.y += 15 + ((angle >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(angle);
	_img->setAnglePos(Vector2(_img->getWidth() * 0.3f, _img->getHeight() * 0.5f));
	_img->render(renderPos, isLeft);


}

void ShortSword::displayInfo()
{
}

void ShortSword::attack(Vector2 const position, float const angle)
{
	if (_currAttackDelay > 0) return;

	_reverseMove = false;
	_attackAngle = angle;
	_currAttackDelay = _baseAttackDelay;
}

void ShortSword::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void ShortSword::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void ShortSword::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void ShortSword::getHit(Vector2 const position)
{
}

PlayerStat ShortSword::equip()
{
	return PlayerStat();
}
