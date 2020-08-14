#include "OakBow.h"
#include "NormalProjectile.h"

void OakBow::init()
{
	_type = ITEM_TYPE::WEAPON_TWO_HAND;
	_rank = ITEM_RANK::NORMAL;
	_iconImg = IMAGE_MANAGER->findImage("OakBow");
	_img = IMAGE_MANAGER->findImage("OakBowAni");

	_price = 360;
	_minDamage = 20;
	_maxDamage = 35;

	// private 변수 설정
	_minDamage = 12;
	_maxDamage = 18;
	_baseAttackDelay = 0.1;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.0001f;
	_currReloadDelay = 0;
	_drawEffect = false;
	_isAttack = false;
	effectCount = 0;

	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, false);
	_ani->stop();
}

void OakBow::release()
{
}

void OakBow::update(Player * player, float const elapsedTime)
{

	if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	else if (_currReloadDelay > 0) // 재장전 중
	{
		_currReloadDelay = max(0, _currReloadDelay - elapsedTime);
		if (_currReloadDelay == 0) // 장전이 끝난 경우
		{
			_currBullet = _maxBullet;
		}
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();



	if (_ani->isPlay())
	{
		_ani->frameUpdate(elapsedTime);
	}

	if (_ani->getPlayIndex() == 3)
	{
		effectCount++;
		if (effectCount == 1)
		{
			_drawEffect = true;						// 이펙트 그리기
		}
		else
		{
			_drawEffect = false;
		}
	}

	renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15; // 플레이어의 중점으로부터 무기를 들고 있는 높이

	// 손으로부터 마우스 에임까지의 각도
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}
	renderPosWeapon = (isLeft) ? Vector2(renderPosHand.x - 9.0f, renderPosHand.y) : Vector2(renderPosHand.x + 9.0f, renderPosHand.y);

	anglePos = Vector2(0.35f * _img->getFrameSize().x, 0.5f * _img->getFrameSize().y);

	if (_isAttack)
	{
		//떼면 공격
		if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
			if (_currBullet == 0) // 총알이 없다면
			{
				if (_currReloadDelay == 0) // 재장전 중이 아니라면
				{
					_currReloadDelay = _baseReloadDelay; // 재장전 함
				}
				return;
			}

			effectCount = 0;

			_ani->setFPS(6);
			_ani->setPlayFrame(4, 6, false);
			_ani->start();

			if (_ani->getPlayIndex() >= 5)
			{
				_ani->stop();
			}

			float length = _img->getFrameSize().x * 0.5f * 3; // 무기 길이만큼

			Vector2 arrowPos = renderPosWeapon;
			arrowPos.x = (isLeft) ? (renderPosWeapon.x + anglePos.x + 15) : (renderPosWeapon.x + anglePos.x);
			arrowPos.y = (isLeft) ? (renderPosWeapon.y + 10) : (renderPosWeapon.y);

			NormalProjectile* projectile = new NormalProjectile;
			projectile->setPosition(arrowPos);
			projectile->setSize(Vector2(80, 15));
			projectile->setTeam(OBJECT_TEAM::PLAYER);
			projectile->init("Arrow00", angleRadian, 30 * 50, false, false, 20, false, "", Vector2());

			AttackInfo* attackInfo = new AttackInfo;
			attackInfo->team = OBJECT_TEAM::PLAYER;
			player->attack(projectile, attackInfo);
			_currAttackDelay = _baseAttackDelay;	// 공격 쿨타임 설정
			_currBullet -= 1;						// 탄환 1 줄임

			if (_isAttack)
			{
				_isAttack = false;
			}
		}
	}
}

void OakBow::backRender(Player * player)
{
}

void OakBow::frontRender(Player * player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	// 손으로부터 마우스 에임까지의 각도
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
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

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(anglePos);
	_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);

	subHandPos = renderPosHand; // 보조 손 (양손무기) 움직임
	subHandPos.x += _img->getFrameSize().x * 0.35 * 3;
	subHandPos.y += (isLeft) ? (_img->getFrameSize().y * -0.1 * 4) : (_img->getFrameSize().y * 0.1 * 4);

	//손 그리기 어케해야하누...음...
	Vector2 renderSunHandPos = subHandPos;

	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	//이펙트
	if (_drawEffect)
	{
		_drawEffect = false;
		Vector2 effectPos01 = renderPosHand; // 손의 위치로부터

		Vector2 effectSize01 = Vector2(50, 50);
		float length = _img->getFrameSize().x * 0.6f * 4; // 무기 길이만큼
		effectPos01.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		effectPos01.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.1) : (0.1))) * length;

		EFFECT_MANAGER->play("L_Effect_Charge", effectPos01, effectSize01, degree);
	}
}

void OakBow::displayInfo()
{
}

void OakBow::attack(Player * player)
{
	if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	if (_currBullet == 0) // 총알이 없다면
	{
		if (_currReloadDelay == 0) // 재장전 중이 아니라면
		{
			_currReloadDelay = _baseReloadDelay; // 재장전 함
		}
		return;
	}

	_ani->setFPS(6);
	_ani->setPlayFrame(0, 4, false);
	_ani->start();

	if (_ani->getPlayIndex() >= 3)
	{
		_drawEffect = true;						// 이펙트 그리기
	}

	if (!_isAttack)
	{
		_isAttack = true;
	}
}

void OakBow::attack(FloatRect * rect, AttackInfo * info)
{
}

void OakBow::attack(FloatCircle * circle, AttackInfo * info)
{
}

void OakBow::attack(Projectile * projectile, AttackInfo * info)
{
}

void OakBow::getHit(Vector2 const position)
{
}

void OakBow::equip(Player* player)
{
}
