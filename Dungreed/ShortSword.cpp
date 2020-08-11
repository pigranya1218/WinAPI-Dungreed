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

void ShortSword::backRender(Player* player)
{

}

void ShortSword::frontRender(Player* player)
{
	Vector2 pos = player->getPosition();
	Vector2 renderPos = pos;

	float angle = atan2f(-(_ptMouse.y - renderPos.y), (_ptMouse.x - renderPos.x)) * (180 / PI) + 360;
	if (angle > 360)
	{
		angle -= 360;
	}


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

void ShortSword::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	// 손으로부터 마우스 에임까지의 각도
	float angle = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}

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
