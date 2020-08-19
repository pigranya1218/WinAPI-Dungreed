#include "NormalProjectile.h"
#include "MatchLockGun.h"

void MatchLockGun::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("MatchlockGun");
	_price = 850;

	_reloadEffect = IMAGE_MANAGER->findImage("ReloadFinish");
	_reloadAni = new Animation;
	_reloadAni->init(_reloadEffect->getWidth(), _reloadEffect->getHeight(), _reloadEffect->getMaxFrameX(), _reloadEffect->getMaxFrameY());
	_reloadAni->setDefPlayFrame(false, false);
	_reloadAni->setFPS(15);

	_itemCode = 0x02261;
	_itemName = L"화승총";
	_displayText = L"\"비가 오면 사용할 수 없는 총\"";

	// 기본 보조옵션
	_addStat.minDamage = 30;
	_addStat.maxDamage = 40;
	_addStat.attackSpeed = 1;
	_addStat.reloadSpeed = 1;

	// private 변수 설정
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_currReloadDelay = 0;
	_drawEffect = false;
}

void MatchLockGun::release()
{

}

void MatchLockGun::update(Player* player, float const elapsedTime)
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
			_reloadAni->start();
		}
	}
	_reloadAni->frameUpdate(elapsedTime);
}

void MatchLockGun::backRender(Player* player)
{
}

void MatchLockGun::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.1f * 4) : -(_img->getWidth() * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15; // 플레이어의 중점으로부터 무기를 들고 있는 높이
	
	// 손으로부터 마우스 에임까지의 각도
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x += ((isLeft) ? -(_img->getWidth() * 0.2f * 4) : (_img->getWidth() * 0.2f * 4));
	renderPosWeapon.y -= _img->getHeight() * 0.1f * 4;
	float renderDegree = degree;
	if (isLeft) // 왼쪽을 보고 있음
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(Vector2(0.3f * _img->getWidth(), 0.6f * _img->getHeight()));
	_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);

	Vector2 subHandPos = renderPosHand; // 보조 손 (양손무기)
	subHandPos.x +=  _img->getWidth() * 0.4 * 4;
	subHandPos.y += (isLeft)?(_img->getHeight() * 0.2 * 4):(_img->getHeight() * -0.2 * 4);
	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	if (_drawEffect) // 이펙트를 그린다
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // 손의 위치로부터

		/*Vector2 effectPos;
		effectPos.x = (isLeft) ? (renderPosHand.x + 18) : (renderPosHand.x - 18);
		effectPos.y = renderPosHand.y;*/

		Vector2 effectSize = Vector2(220, 220);
		float length = _img->getWidth() * 0.6f * 4; // 무기 길이만큼
		effectPos.x += cosf(degree * (PI / 180) + ((isLeft)?(-0.2):(0.2))) * length;
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;

		/*float changeX = cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		effectPos.x += (isLeft) ? (changeX + 18) : (changeX - 18);
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;*/

		EFFECT_MANAGER->play("L_Effect_HecateSmoke", effectPos, effectSize, degree);

		Image* effectImg = IMAGE_MANAGER->findImage("ShootEffect");
		Vector2 effectSize02 = Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4);

		float length02 = _iconImg->getWidth() * 0.6f * 3; // 무기 길이만큼
		effectPos.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length02;
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length02;

		EFFECT_MANAGER->play("L_Effect_Shoot", effectPos, effectSize02, degree);
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

void MatchLockGun::displayInfo()
{
}

void MatchLockGun::attack(Player* player)
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
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.1f * 4) : -(_img->getWidth() * 0.1f * 4)); // 손의 위치는 무기의 회전 중심점
	renderPosHand.y += 15; // 플레이어의 중점으로부터 무기를 들고 있는 높이

	// 손으로부터 마우스 에임까지의 각도
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	Vector2 shootPos = renderPosHand;
	float length = _img->getWidth() * 0.6f * 4; // 무기 길이만큼
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	Image* _bulletImg = IMAGE_MANAGER->findImage("GunBullet");

	projectile = new NormalProjectile;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(_bulletImg->getFrameSize().x * 4, _bulletImg->getFrameSize().y * 4));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("GunBullet", angleRadian, 30 * 50, true, false, 10, false, "", Vector2(), 800);	// 사정거리 추가했어요 >> 황수현

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // 아이템 코드와 현재 시간을 Concat하여 공격 아이디를 구하기 위한 공격 코드를 생성함

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 30;

	player->attack(projectile, attackInfo);
	_currAttackDelay = _adjustStat.attackSpeed; // 공격 쿨타임 설정
	_currBullet -= 1; // 탄환 1 줄임
	_drawEffect = true; // 이펙트 그리기
}

void MatchLockGun::attack(FloatRect * rect, AttackInfo* info)
{
}

void MatchLockGun::attack(FloatCircle * circle, AttackInfo* info)
{
}

void MatchLockGun::attack(Projectile * projectile, AttackInfo* info)
{
}

void MatchLockGun::reload(Player * player)
{
	if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	if (_currReloadDelay == 0) // 재장전 중이 아니라면
	{
		_currReloadDelay = _adjustStat.reloadSpeed; // 재장전 함
	}
}

void MatchLockGun::getHit(Vector2 const position)
{
}

void MatchLockGun::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// 플레이어의 공격속도가 30이라면 원래 공격속도의 (100 - 30)%로 공격함 = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
	_adjustStat.reloadSpeed = _addStat.reloadSpeed * ((100 - stat.reloadSpeed) / 100);
}

wstring MatchLockGun::getBulletUI()
{
	return to_wstring(_currBullet) + L"/" + to_wstring(_maxBullet);
}

float MatchLockGun::getBulletRatio()
{
	return _currReloadDelay / _adjustStat.reloadSpeed;
}

NormalProjectile* MatchLockGun::getBulletInfo()
{
	return projectile;
}
