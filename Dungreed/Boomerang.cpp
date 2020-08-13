#include "Boomerang.h"

void Boomerang::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("MetalBoomerang");
	_type = ITEM_TYPE::WEAPON_TWO_HAND;
	_rank = ITEM_RANK::RARE;

	_price = 550;
	_minDamage = 16;
	_maxDamage = 19;
	_gunType = 4;
	_isAttack = false;

	_aniImg = IMAGE_MANAGER->findImage("Boomerang_Moving");
	_ani = new Animation;
	_ani->init(_aniImg->getWidth(), _aniImg->getHeight(), 2, 1);
	_ani->setPlayFrame(0, 2, false, true);
	_ani->setFPS(15);
}

void Boomerang::release()
{
}

void Boomerang::update(float const elapsedTime)
{
	if (_isAttack)
	{
		_timeCount++;


		//_ani->frameUpdate(elapsedTime);
		if (!_ani->isPlay())
		{
			_ani->start();
		}

		if (_timeCount == 50)
		{
			_timeCount = 0;
			_ani->stop();
			_isAttack = false;
		}

		_ani->frameUpdate(elapsedTime);
	}
}

void Boomerang::render(Vector2 pos, float angle)
{
	Vector2 _centerPos = Vector2(_img->getSize().x / 2, _img->getSize().y / 2);
	_img->setScale(4);
	_img->setAnglePos(_centerPos);

	_isLeft = false;
	if (angle >= 90 && angle <= 270) // 왼쪽을 보고 있음
	{
		_isLeft = true;
		angle = fmod((180 - angle) + 360, 360);
	}

	
	_gunPos = _isLeft ? Vector2(pos.x - 20, pos.y + 15) : Vector2(pos.x + 20, pos.y + 15);

	Vector2 size = Vector2(_aniImg->getFrameSize().x * 4, _aniImg->getFrameSize().y * 4);
	_attackRect = rectMakePivot(_gunPos, size, PIVOT::CENTER);

	/*if (_isLeft) { _gunPos = Vector2(pos.x - 20, pos.y + 15); }
	else { _gunPos = Vector2(pos.x + 20, pos.y + 15); }*/

	_img->setAngle(angle);

	if (!_isAttack)
	{
		_img->render(_gunPos, _isLeft);
	}
	if (_isAttack)
	{
		_aniImg->setScale(4);
		_aniImg->aniRender(_gunPos, _ani, _isLeft);
		D2D_RENDERER->drawRectangle(_attackRect);
	}
}

void Boomerang::displayInfo()
{
}

void Boomerang::attack(Vector2 const position, float const angle)
{
	if (!_isAttack) { _isAttack = true; }
	//float angle = fmod(atan2f(-(_ptMouse.y - (_position.y + 15)), (_ptMouse.x - _position.x)) * (180 / PI) + 360, 360);

}

void Boomerang::attack(FloatRect * rect, AttackInfo * info)
{
}

void Boomerang::attack(FloatCircle * circle, AttackInfo * info)
{
}

void Boomerang::attack(Projectile * projectile, AttackInfo * info)
{
}

void Boomerang::getHit(Vector2 const position)
{
}

PlayerStat Boomerang::equip()
{
	return PlayerStat();
}
