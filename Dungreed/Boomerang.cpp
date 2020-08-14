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

void Boomerang::update(Player * player, float const elapsedTime)
{
	if (_isAttack)
	{
		_timeCount++;
		//_ani->frameUpdate(elapsedTime);
		if (!_ani->isPlay())
		{
			_ani->start();
		}

		if (_timeCount == 100)
		{
			_timeCount = 0;
			_ani->stop();
			_isAttack = false;
		}
		_ani->frameUpdate(elapsedTime);
	}

	_isLeft = (player->getDirection() == DIRECTION::LEFT);

	Vector2 renderPosHand = _pos;
	renderPosHand.x += ((_isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15;

	// 손으로부터 마우스 에임까지의 각도
	_degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (_degree > 360)
	{
		_degree -= 360;
	}

	_renderDegree = _degree;
	if (_isLeft) // 왼쪽을 보고 있음
	{
		_renderDegree = 180 - _degree;
		if (_renderDegree < 0) _renderDegree += 360;
	}

	_pos = player->getPosition();

	if (!_isAttack)
	{
		_gunPos = _isLeft ? Vector2(_pos.x - 20, _pos.y + 15) : Vector2(_pos.x + 20, _pos.y + 15);
	}

	if (_isAttack)
	{
		float speed = 5.0f;

		_gunPos.x += cosf((_degree) * (PI / 180)) * speed;
		_gunPos.y += -sinf((_degree) * (PI / 180)) * speed;
	}
}

void Boomerang::backRender(Player * player)
{
}

void Boomerang::frontRender(Player * player)
{
	
	Vector2 _centerPos = Vector2(_img->getSize().x / 2, _img->getSize().y / 2);
	_img->setScale(4);
	_img->setAnglePos(_centerPos);

	Vector2 size = Vector2(_aniImg->getFrameSize().x * 4, _aniImg->getFrameSize().y * 4);
	_attackRect = rectMakePivot(_gunPos, size, PIVOT::CENTER);

	/*if (_isLeft) { _gunPos = Vector2(pos.x - 20, pos.y + 15); }
	else { _gunPos = Vector2(pos.x + 20, pos.y + 15); }*/

	_img->setAngle(_renderDegree);

	if (!_isAttack)
	{
		_img->render(CAMERA->getRelativeV2(_gunPos), _isLeft);
	}
	if (_isAttack)
	{
		_aniImg->setScale(4);
		_aniImg->aniRender(CAMERA->getRelativeV2(_gunPos), _ani, _isLeft);
		D2D_RENDERER->drawEllipse(CAMERA->getRelativeV2(_gunPos), _aniImg->getFrameSize().x * 2, D2D1::ColorF::Black, 1.0f, 1.0f);
	}
}

void Boomerang::displayInfo()
{
}

void Boomerang::attack(Player * player)
{
	if (!_isAttack) { _isAttack = true; }
	
	
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
