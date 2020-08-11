#include "MatchLockGun.h"

void MatchLockGun::init()
{
	_img = IMAGE_MANAGER->findImage("MatchlockGun");
	_type = ITEM_TYPE::WEAPON_TWO_HAND;
	_rank = ITEM_RANK::NORMAL;

	_price = 250;
	_minDamage = 30;
	_maxDamage = 40;
	_bulletCount = 1;
	_reloadCount = 3.0f;
}

void MatchLockGun::release()
{
}

void MatchLockGun::update(Player* player, float const elapsedTime)
{

}

void MatchLockGun::backRender(Player* player)
{
}

void MatchLockGun::frontRender(Player* player)
{
	Vector2 _centerPos = Vector2(_img->getSize().x / 3, _img->getSize().y / 2);
	_img->setScale(3);
	_img->setAnglePos(_centerPos);

	/*_img->setAngle(angle);

	if (angle < 90.0f && angle >= 0.0f && angle > 270.0f && angle <= 360.0f)
	{
		_isLeft = false;
	}
	if (angle > 90.0f && angle < 270.0f)
	{
		_isLeft = true;
	}

	_img->render(pos, _isLeft);*/

	//D2DRenderer::renderText(50, 50, );
}

void MatchLockGun::displayInfo()
{
}

void MatchLockGun::attack(Player* player)
{
}

void MatchLockGun::attack(FloatRect * rect, tagAttackInfo * info)
{
}

void MatchLockGun::attack(FloatCircle * circle, tagAttackInfo * info)
{
}

void MatchLockGun::attack(Projectile * projectile, tagAttackInfo * info)
{
}

void MatchLockGun::getHit(Vector2 const position)
{
}

PlayerStat MatchLockGun::equip()
{
	return PlayerStat();
}
