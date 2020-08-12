#include "MatchLockGun.h"

void MatchLockGun::init()
{
	_img = IMAGE_MANAGER->findImage("MatchlockGun");
	_type = ITEM_TYPE::WEAPON_TWO_HAND;
	_rank = ITEM_RANK::NORMAL;

	_dustEffect = IMAGE_MANAGER->findImage("HecateSmokeFX02");
	_shootEffect = IMAGE_MANAGER->findImage("ShootEffect02");

	_price = 250;
	_minDamage = 30;
	_maxDamage = 40;
	_gunType = 0;
	_isAttack = false;

	_effectAni01 = new Animation;
	_effectAni01->init(_dustEffect->getWidth(), _dustEffect->getHeight(), 10, 1);
	_effectAni01->setDefPlayFrame(false, false);
	_effectAni01->setFPS(20);

}

void MatchLockGun::release()
{
}

void MatchLockGun::update(float const elapsedTime)
{
	if (_isAttack)
	{
		/*if (!_effectAni01->isPlay())
		{
			_effectAni01->start();
		}*/

		_effectAni01->frameUpdate(elapsedTime);
		//_bullet->update(elapsedTime);
	}
}

void MatchLockGun::render(Vector2 pos, float angle)
{
	Vector2 _centerPos = Vector2(_img->getSize().x / 3, _img->getSize().y / 2);
	_img->setScale(4);
	_img->setAnglePos(_centerPos);

	_isLeft = false;
	if (angle >= 90 && angle <= 270) // 왼쪽을 보고 있음
	{
		_isLeft = true;
		angle = fmod((180 - angle) + 360, 360);
	}

	_gunPos = _isLeft ? Vector2(pos.x - 20, pos.y + 15) : Vector2(pos.x + 20, pos.y + 15);

	/*if (_isLeft) { _gunPos = Vector2(pos.x - 20, pos.y + 15); }
	else { _gunPos = Vector2(pos.x + 20, pos.y + 15); }*/

	_img->setAngle(angle);
	_img->render(_gunPos, _isLeft);

	Vector2 _pos;
	Vector2 _centerPos02 = Vector2(_img->getSize().x * 0.25f, _img->getSize().y / 2);
	_dustEffect->setScale(4);
	_dustEffect->setAnglePos(_centerPos02);
	if (_isAttack)
	{
		_dustEffect->setScale(4);
		//_dustEffect->setAnglePos(_centerPos);
		/*if (!_isLeft)
		{
			_pos = Vector2(pos.x + 30, pos.y + 5);

		}
		else
		{
			_pos = Vector2(pos.x - 30, pos.y + 5);
		}*/
		_dustEffect->setAngle(angle);
		_dustEffect->aniRender(_gunPos, _effectAni01, _isLeft);
		//_bullet->render();
	}

	//D2DRenderer::renderText(50, 50, );
}

void MatchLockGun::displayInfo()
{
}

void MatchLockGun::attack(Vector2 const position, float const angle)
{
	_isAttack = true;
	_effectAni01->start();
	//_bullet->init(1, position);
	//_bullet->fire(position, angle);

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
