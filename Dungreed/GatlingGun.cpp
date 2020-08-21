#include "GatlingGun.h"

void GatlingGun::init()
{
	_itemCode = 0x02361;
	_itemName = L"N134 개틀링 기관총";
	_displayText = L"\"원본인 개틀링 기관총보다 작아져서 미니건이다.\"";

	_iconImg = IMAGE_MANAGER->findImage("GatlingGun");
	_price = 1800;

	_addStat.minDamage = 2;
	_addStat.maxDamage = 6;
	_addStat.attackSpeed = 0.05;
	_addStat.reloadSpeed = 4;

	// private 변수 설정
	_currAttackDelay = 0;
	_maxBullet = 100;
	_currBullet = _maxBullet;
	_currReloadDelay = 0;

	//개틀링건 돌아가는 애니메이션
	_attackImg = IMAGE_MANAGER->findImage("GatlingGun_Ani");
	_attackAni = new Animation;
	_attackAni->init(_attackImg->getWidth(), _attackImg->getHeight(), _attackImg->getMaxFrameX(), _attackImg->getMaxFrameY());
	_attackAni->setDefPlayFrame(false, true);
	_attackAni->setFPS(10);

	//재장전 애니메이션
	_reloadEffect = IMAGE_MANAGER->findImage("ReloadFinish");
	_reloadAni = new Animation;
	_reloadAni->init(_reloadEffect->getWidth(), _reloadEffect->getHeight(), _reloadEffect->getMaxFrameX(), _reloadEffect->getMaxFrameY());
	_reloadAni->setDefPlayFrame(false, false);
	_reloadAni->setFPS(15);

	//쏠때 이펙트
	_shootEffectImg = IMAGE_MANAGER->findImage("ShootEffect");
	_shootEffectAni = new Animation;
	_shootEffectAni->init(_shootEffectImg->getWidth(), _shootEffectImg->getHeight(), _shootEffectImg->getMaxFrameX(), _shootEffectImg->getMaxFrameY());
	_shootEffectAni->setDefPlayFrame(false, false);
	_shootEffectAni->setFPS(15);
}

void GatlingGun::release()
{
}

void GatlingGun::update(Player * player, float const elapsedTime)
{
	if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	else if (_currReloadDelay > 0) // 재장전 중
	{
		_currReloadDelay = max(0, _currReloadDelay - elapsedTime);
		_attackAni->stop();

		if (_currReloadDelay == 0) // 장전이 끝난 경우
		{
			_currBullet = _maxBullet;
			_reloadAni->start();
		}
	}
	_attackAni->frameUpdate(elapsedTime);
	_reloadAni->frameUpdate(elapsedTime);
	_shootEffectAni->frameUpdate(elapsedTime);

	if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		_attackAni->stop();
		_shootEffectAni->stop();
	}
}

void GatlingGun::backRender(Player * player)
{
}

void GatlingGun::frontRender(Player * player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_iconImg->getWidth() * 0.1f * 4) : -(_iconImg->getWidth() * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15; // 플레이어의 중점으로부터 무기를 들고 있는 높이

	// 손으로부터 마우스 에임까지의 각도
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x += ((isLeft) ? -(_iconImg->getWidth() * 0.2f * 4) : (_iconImg->getWidth() * 0.2f * 4));
	renderPosWeapon.y -= _iconImg->getHeight() * 0.1f * 4;
	float renderDegree = degree;
	if (isLeft) // 왼쪽을 보고 있음
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	if (!_attackAni->isPlay())
	{
		_iconImg->setScale(4);
		_iconImg->setAngle(renderDegree);
		_iconImg->setAnglePos(Vector2(0.3f * _iconImg->getWidth(), 0.6f * _iconImg->getHeight()));
		_iconImg->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);
	}

	if (_attackAni->isPlay())
	{
		_attackImg->setScale(4);
		_attackImg->setAngle(renderDegree);
		_attackImg->setAnglePos(Vector2(0.3f * _iconImg->getWidth(), 0.6f * _iconImg->getHeight()));
		_attackImg->aniRender(CAMERA->getRelativeV2(renderPosWeapon), _attackAni, isLeft);
	}

	Vector2 subHandPos = renderPosHand; // 보조 손 (양손무기)
	subHandPos.x += _iconImg->getWidth() * 0.4 * 4;
	subHandPos.y += (isLeft) ? (_iconImg->getHeight() * 0.2 * 4) : (_iconImg->getHeight() * -0.2 * 4);
	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	//D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	//D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));
	
	Vector2 renderPosHand02 = pos;
	renderPosHand02.x += ((isLeft) ? (_iconImg->getWidth() * 0.1f * 4) : -(_iconImg->getWidth() * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand02.y += 30; // 플레이어의 중점으로부터 무기를 들고 있는 높이

	//if (_drawEffect) // 발사 이펙트를 그린다
	//{
	//	_drawEffect = false;
	//	Vector2 effectPos = renderPosHand; // 손의 위치로부터
	//	effectPos.x += 5;
	//	//effectPos.y = renderPosHand.y + 15;

	//	Image* effectImg = IMAGE_MANAGER->findImage("ShootEffect");
	//	Vector2 effectSize = Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4);

	//	float length = _iconImg->getWidth() * 0.6f * 7; // 무기 길이만큼
	//	effectPos.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
	//	effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;

	//	EFFECT_MANAGER->play("L_Effect_Shoot", effectPos, effectSize, degree);
	//}

	if (_shootEffectAni->isPlay())
	{
		Vector2 shootEffectPos = renderPosHand;
		
		//shootEffectPos.x += renderPosHand.x + 70;
		//shootEffectPos.y = renderPosHand.y + 25;

		float length = _iconImg->getWidth() * 1.00f * 4; // 무기 길이만큼
		shootEffectPos.x += cosf(degree * (PI / 180)) * length;
		shootEffectPos.y += -sinf(degree * (PI / 180)) * length;



		_shootEffectImg->setAngle(degree);
		//_shootEffectImg->setAnglePos(Vector2(0.0f, _shootEffectImg->getFrameSize().y * 0.5f));
		_shootEffectImg->setScale(4);
		_shootEffectImg->aniRender(CAMERA->getRelativeV2(shootEffectPos), _shootEffectAni);
	}

	// 재장전 중이라면 재장전 UI를 그린다.
	if (_currReloadDelay > 0)
	{
		float ratio = _currReloadDelay / _adjustStat.reloadSpeed;
		FloatRect reloadBar = FloatRect(Vector2(pos.x, pos.y - 60), Vector2(92, 4), PIVOT::CENTER);
		FloatRect reloadHandle = FloatRect(Vector2(reloadBar.right - ratio * reloadBar.getSize().x, reloadBar.getCenter().y), Vector2(8, 12), PIVOT::CENTER);
		IMAGE_MANAGER->findImage("ReloadBar")->render(CAMERA->getRelativeV2(reloadBar.getCenter()), reloadBar.getSize());
		IMAGE_MANAGER->findImage("ReloadHandle")->render(CAMERA->getRelativeV2(reloadHandle.getCenter()), reloadHandle.getSize());
	}
	if (_reloadAni->isPlay())
	{
		_reloadEffect->setScale(4);
		_reloadEffect->aniRender(CAMERA->getRelativeV2(Vector2(pos.x, pos.y - 60)), _reloadAni);
	}
}

void GatlingGun::displayInfo()
{
}

void GatlingGun::attack(Player * player)
{
	if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	if (_currReloadDelay > 0) return; // 장전 중엔 공격을 하지 않음
	if (_currBullet == 0) // 총알이 없다면
	{
		if (_currReloadDelay == 0) // 재장전 중이 아니라면
		{
			_currReloadDelay = _adjustStat.reloadSpeed; // 재장전 함
		}
		return;
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_iconImg->getWidth() * 0.1f * 4) : -(_iconImg->getWidth() * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 25; // 플레이어의 중점으로부터 무기를 들고 있는 높이

	// 손으로부터 마우스 에임까지의 각도
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2 + RANDOM->getFromFloatTo(-PI * 0.02, PI * 0.02);
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	Vector2 shootPos = renderPosHand;
	float length = _iconImg->getWidth() * 0.6f * 9; // 무기 길이만큼
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.05) : (0.05))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.1) : (0.1))) * length;

	NormalProjectile* projectile = new NormalProjectile;
	projectile->setPosition(shootPos);
	projectile->setTeam(OBJECT_TEAM::PLAYER);

	Image* bulletImg = IMAGE_MANAGER->findImage("GunBullet");
	Vector2 bulletSize = Vector2(bulletImg->getFrameSize().x * 4, bulletImg->getFrameSize().y * 4);
	Vector2 bulletRect = Vector2(bulletImg->getFrameSize().x, bulletImg->getFrameSize().x);

	Image* effectImg = IMAGE_MANAGER->findImage("GatlingGunEffect");
	Vector2 effectSize = Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4);

	//projectile->init("GunBullet", angleRadian, 30 * 50, true, false, 10, true, "", Vector2(), 800);	// 사정거리 추가했어요 >> 황수현
	projectile->init("GunBullet", "L_Effect_GatlingGunBullet", bulletSize, bulletRect, effectSize, Vector2(30 * 50, 30 * 50), 0.6f, angleRadian, true, false, 10, true, false, true, false);	// 함수 인자가 많이 바뀌었어요 >> 확인해주세요.

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->madeByWeapon = true;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 30;

	player->attack(projectile, attackInfo);

	SOUND_MANAGER->stop("GatlingFire");
	SOUND_MANAGER->play("GatlingFire", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
	
	_currAttackDelay = _adjustStat.attackSpeed; // 공격 쿨타임 설정
	_currBullet -= 1; // 탄환 1 줄임
	_drawEffect = true; // 이펙트 그리기

	_attackAni->start();
	_shootEffectAni->start();
}

void GatlingGun::attack(Player* player, FloatRect * rect, AttackInfo * info)
{
}

void GatlingGun::attack(Player* player, FloatCircle * circle, AttackInfo * info)
{
}

void GatlingGun::attack(Player* player, Projectile * projectile, AttackInfo * info)
{
}

void GatlingGun::reload(Player * player)
{
	if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	if (_currReloadDelay == 0) // 재장전 중이 아니라면
	{
		_currReloadDelay = _adjustStat.reloadSpeed; // 재장전 함
	}
}

void GatlingGun::getHit(Vector2 const position)
{
}

void GatlingGun::equip(Player * player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
	_adjustStat.reloadSpeed = _addStat.reloadSpeed * ((100 - stat.reloadSpeed) / 100);
}

wstring GatlingGun::getBulletUI()
{
	return to_wstring(_currBullet) + L"/" + to_wstring(_maxBullet);
}

float GatlingGun::getBulletRatio()
{
	return _currReloadDelay / _adjustStat.reloadSpeed;
}
