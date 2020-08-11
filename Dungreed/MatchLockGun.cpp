#include "MatchLockGun.h"

void MatchLockGun::init()
{
	_img = IMAGE_MANAGER->findImage("MatchlockGun");
	_type = ITEM_TYPE::WEAPON_TWO_HAND;
	_rank = ITEM_RANK::NORMAL;
	_price = 250;
}

void MatchLockGun::release()
{
}

void MatchLockGun::update(float const elapsedTime)
{

}

void MatchLockGun::render(Vector2 pos, float angle)
{
	Vector2 _centerPos = Vector2(_img->getSize().x / 3, _img->getSize().y / 2);
	_img->setScale(3);
	_img->setAnglePos(_centerPos);
	_img->render(pos);
}

void MatchLockGun::displayInfo()
{
}

void MatchLockGun::attack(Vector2 const position, float const angle)
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
