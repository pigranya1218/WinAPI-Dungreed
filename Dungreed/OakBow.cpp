#include "OakBow.h"
#include "NormalProjectile.h"

void OakBow::init()
{
	_iconImg = IMAGE_MANAGER->findImage("OakBow");
	_img = IMAGE_MANAGER->findImage("OakBowAni");

	_itemCode = 0x02161;
	_itemName = L"떡갈나무 활";
	_displayText = L"\"단단해서 때리는 데 쓸 수도 있을 것 같습니다.\"";

	// 기본 보조옵션
	
	_addStat.attackSpeed = 1;
	_addStat.reloadSpeed = 0.1;

	_price = 360;

	// private 변수 설정
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_currReloadDelay = 0;
	_drawEffect = false;
	_isAttack = false;
	_isFrameUpdate = false;
	_effectCount = 0;
	_frameCount = 0;
	_timeCount = 0;

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
	_frameTimeCount = elapsedTime;
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

	//if (_ani->getPlayIndex() == 3)
	//{
	//	_effectCount++;
	//	if (_effectCount == 20)
	//	{
	//		_drawEffect = true;						// 이펙트 그리기
	//	}
	//	else
	//	{
	//		_drawEffect = false;
	//	}
	//}

	renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15; // 플레이어의 중점으로부터 무기를 들고 있는 높이

	subHandPos = renderPosHand; // 보조 손 (양손무기) 움직임
	subHandPos.x += _img->getFrameSize().x * 0.35 * 3;
	subHandPos.y += (isLeft) ? (_img->getFrameSize().y * -0.1 * 4) : (_img->getFrameSize().y * 0.1 * 4);

	// 손으로부터 마우스 에임까지의 각도
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	//이펙트 각도값
	_effectAngleRadianValue = angleRadian;

	renderPosWeapon = (isLeft) ? Vector2(renderPosHand.x - 9.0f, renderPosHand.y) : Vector2(renderPosHand.x + 9.0f, renderPosHand.y);

	anglePos = Vector2(0.35f * _img->getFrameSize().x, 0.5f * _img->getFrameSize().y);

	if (_isAttack)
	{
		//_ani->setFPS(1);
		//_ani->setPlayFrame(0, 4, false);
		//_ani->start();

		//떼면 공격
		if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
			if (_currBullet == 0) // 총알이 없다면
			{
				if (_currReloadDelay == 0) // 재장전 중이 아니라면
				{
					_currReloadDelay = _adjustStat.reloadSpeed; // 재장전 함
				}
				return;
			}
			
			_effectCount = 0;

			_ani->setFPS(10);
			_ani->setPlayFrame(4, 6, false);
			_ani->start();

			if (_ani->getPlayIndex() >= 5)
			{
				_ani->stop();
			}

			float length = _img->getFrameSize().x * 0.5f * 3; // 무기 길이만큼

			Vector2 arrowPos = renderPosWeapon;
			arrowPos.x = (isLeft) ? (renderPosWeapon.x + anglePos.x + 5) : (renderPosWeapon.x + anglePos.x - 15);
			//arrowPos.y = (isLeft) ? (renderPosWeapon.y + 10) : (renderPosWeapon.y);
			
			Image* effectImg = IMAGE_MANAGER->findImage("ArrowHitEffect");

			NormalProjectile* projectile = new NormalProjectile;
			projectile->setPosition(arrowPos);
			projectile->setSize(Vector2(80, 15));
			projectile->setTeam(OBJECT_TEAM::PLAYER);
			projectile->init("Arrow00", angleRadian, 30 * 50, false, false, 20, true, "L_Effect_ArrowHit", Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4), 800);

			string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

			AttackInfo* attackInfo = new AttackInfo;
			attackInfo->team = OBJECT_TEAM::PLAYER;
			attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
			attackInfo->critical = 0;
			attackInfo->criticalDamage = 0;
			attackInfo->minDamage = _addStat.minDamage;
			attackInfo->maxDamage = _addStat.maxDamage;
			attackInfo->knockBack = 0;

			player->attack(projectile, attackInfo);
			_currAttackDelay = _adjustStat.attackSpeed;	// 공격 쿨타임 설정
			_currBullet -= 1;						// 탄환 1 줄임

			if (_isAttack)
			{
				_isAttack = false;
				_isFrameUpdate = true;
				_frameCount = 0;
			}
		}
	}

	/*if (_isFrameUpdate)
	{
		if (_frameCount == 3)
		{
			_frameCount++;
			if (_frameCount == 5)
			{
				_frameCount = 0;
				_isFrameUpdate = false;
			}
		}
	}*/
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
	
	if (!_ani->isPlay())
	{
		_img->frameRender(CAMERA->getRelativeV2(renderPosWeapon), _frameCount, 0, isLeft);
	}

	if (_ani->isPlay())
	{
		_img->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _ani, isLeft);
	}

	/*if (!_isAttack)
	{
	}*/

	//손 그리기 어케해야하누...음...
	Vector2 renderSunHandPos = subHandPos;

	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	//이펙트
	if (_effectCount == 1)
	{
		Vector2 effectPos01 = renderPosHand; // 손의 위치로부터

		Vector2 effectSize01 = Vector2(50, 50);
		float length = _img->getFrameSize().x * 0.6f * 4; // 무기 길이만큼
		effectPos01.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		effectPos01.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.1) : (0.1))) * length;

		EFFECT_MANAGER->play("L_Effect_Charge", effectPos01, effectSize01, _effectAngleRadianValue);
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
			_currReloadDelay = _adjustStat.reloadSpeed; // 재장전 함
		}
		return;
	}

	if (!_isAttack)
	{
		_isAttack = true;
	}

	_addStat.minDamage = 20;
	_addStat.maxDamage = 25;

	_timeCount++;
	if (_timeCount == 10)
	{
		_timeCount = 0;
		_frameCount++;
	}
	if (_frameCount >= 3)
	{
		_frameCount = 3;
		_effectCount++;

		_addStat.minDamage = 30;
		_addStat.maxDamage = 35;
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
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
	_adjustStat.reloadSpeed = _addStat.reloadSpeed * ((100 - stat.reloadSpeed) / 100);
}

float OakBow::getBulletRatio()
{
	return _currReloadDelay / _adjustStat.reloadSpeed;
}
