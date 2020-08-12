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
	_drawEffect = false;

	_effectAni01 = new Animation;
	_effectAni01->init(_dustEffect->getWidth(), _dustEffect->getHeight(), 10, 1);
	_effectAni01->setDefPlayFrame(false, false);
	_effectAni01->setFPS(20);

	_handSize = Vector2(5, 5);

}

void MatchLockGun::release()
{
}

void MatchLockGun::update(Player* player, float const elapsedTime)
{
	if (_isAttack)
	{
		/*if (!_effectAni01->isPlay())
		{
			_effectAni01->start();
		}*/

		_effectAni01->frameUpdate(elapsedTime);
		_bullet->update(elapsedTime);
	}
}

void MatchLockGun::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	if (isLeft)
	{
		Vector2 renderPos = Vector2(pos.x - 22, pos.y + 20);

		_hand = rectMakePivot(renderPos, _handSize, PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1, 6.f);
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1);
	}
	else
	{
		Vector2 renderPos = Vector2(pos.x + 22, pos.y + 20);

		_hand = rectMakePivot(renderPos, Vector2(_handSize), PIVOT::CENTER);
		D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1, 6.f);
		D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1);
	}
}

void MatchLockGun::frontRender(Player* player)
{
	//Vector2 _centerPos = Vector2(_img->getSize().x / 3, _img->getSize().y / 2);
	//_img->setScale(4);
	//_img->setAnglePos(_centerPos);

	//_isLeft = false;
	//if (angle >= 90 && angle <= 270) // 왼쪽을 보고 있음
	//{
	//	_isLeft = true;
	//	angle = fmod((180 - angle) + 360, 360);
	//}

	//_gunPos = _isLeft ? Vector2(pos.x - 20, pos.y + 15) : Vector2(pos.x + 20, pos.y + 15);

	///*if (_isLeft) { _gunPos = Vector2(pos.x - 20, pos.y + 15); }
	//else { _gunPos = Vector2(pos.x + 20, pos.y + 15); }*/

	//_img->setAngle(angle);
	//_img->render(_gunPos, _isLeft);

	//Vector2 _pos;
	//Vector2 _centerPos02 = Vector2(_img->getSize().x * 0.25f, _img->getSize().y / 2);
	//_dustEffect->setScale(4);
	//_dustEffect->setAnglePos(_centerPos02);
	//if (_isAttack)
	//{
	//	_dustEffect->setScale(4);
	//	//_dustEffect->setAnglePos(_centerPos);
	//	/*if (!_isLeft)
	//	{
	//		_pos = Vector2(pos.x + 30, pos.y + 5);

	//	}
	//	else
	//	{
	//		_pos = Vector2(pos.x - 30, pos.y + 5);
	//	}*/
	//	_dustEffect->setAngle(angle);
	//	_dustEffect->aniRender(_gunPos, _effectAni01, _isLeft);
	//	//_bullet->render();
	//}

	////D2DRenderer::renderText(50, 50, );

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 20; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	// 손으로부터 마우스 에임까지의 각도
	float degree = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x -= ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4));

	float renderDegree = degree;
	if (isLeft) // 왼쪽을 보고 있음
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}
	renderPosWeapon.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));
	renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));
	renderPosHand.x += ((isLeft) ? (-_attackMove.x) : (_attackMove.x));
	renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(Vector2(0.35f * _img->getWidth(), 0.5f * _img->getHeight()));
	_img->render(renderPosWeapon, isLeft);

	_hand = rectMakePivot(renderPosHand, _handSize, PIVOT::CENTER);

	D2D_RENDERER->drawRectangle(_hand, 40, 36, 58, 1.f, 6.f, degree, renderPosHand);
	D2D_RENDERER->fillRectangle(_hand, 210, 188, 181, 1.f, degree, renderPosHand);

	if (_drawEffect) // 이펙트를 그린다
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // 손의 위치로부터
		//float length = _img->getWidth() * 4 * 0.7; // 무기 길이만큼
		float length = 0.0f;
		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;
		// D2D_RENDERER->drawRectangle(FloatRect(effectPos, Vector2(10, 10), PIVOT::CENTER), D2DRenderer::DefaultBrush::Black, 1, angle, effectPos);
		
		Image* effectImage = IMAGE_MANAGER->findImage("HecateSmokeFX02");
		//effectImage->setScale(4);

		EFFECT_MANAGER->play("L_Effect_HecateSmoke", effectPos, Vector2(effectImage->getFrameSize().x * 4, effectImage->getFrameSize().y * 4), degree);
	}

	if (_isAttack)
	{
		_bullet->render();
	}
}

void MatchLockGun::displayInfo()
{
}

void MatchLockGun::attack(Player* player)
{
	_effectAni01->start();
	//_bullet->init(1, position);
	//_bullet->fire(position, angle);
	_drawEffect = true;

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	float degree = atan2f(-(_ptMouse.y - player->getPosition().y), (_ptMouse.x - player->getPosition().x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	float renderDegree = degree;
	if (isLeft) // 왼쪽을 보고 있음
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	_bullet = new PlayerBullet;
	_bullet->init(player->getPosition(), renderDegree);
	_isAttack = true;
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
