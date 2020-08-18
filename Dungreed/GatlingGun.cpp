#include "GatlingGun.h"

void GatlingGun::init()
{
	_itemCode = 0x02361;
	_itemName = L"N134 ��Ʋ�� �����";
	_displayText = L"\"������ ��Ʋ�� ����Ѻ��� �۾����� �̴ϰ��̴�.\"";

	_iconImg = IMAGE_MANAGER->findImage("GatlingGun");
	_price = 1800;

	_addStat.minDamage = 2;
	_addStat.maxDamage = 6;
	_addStat.attackSpeed = 21.74;

	// private ���� ����
	_baseAttackDelay = 0.05;
	_currAttackDelay = 0;
	_maxBullet = 100;
	_currBullet = _maxBullet;
	_baseReloadDelay = 4;
	_currReloadDelay = 0;

	//��Ʋ���� ���ư��� �ִϸ��̼�
	_attackImg = IMAGE_MANAGER->findImage("GatlingGun_Ani");
	_attackAni = new Animation;
	_attackAni->init(_attackImg->getWidth(), _attackImg->getHeight(), _attackImg->getMaxFrameX(), _attackImg->getMaxFrameY());
	_attackAni->setDefPlayFrame(false, true);
	_attackAni->setFPS(10);

	//������ �ִϸ��̼�
	_reloadEffect = IMAGE_MANAGER->findImage("ReloadFinish");
	_reloadAni = new Animation;
	_reloadAni->init(_reloadEffect->getWidth(), _reloadEffect->getHeight(), _reloadEffect->getMaxFrameX(), _reloadEffect->getMaxFrameY());
	_reloadAni->setDefPlayFrame(false, false);
	_reloadAni->setFPS(15);
}

void GatlingGun::release()
{
}

void GatlingGun::update(Player * player, float const elapsedTime)
{
	if (_currAttackDelay > 0) // ���� ������ ��� ��
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	else if (_currReloadDelay > 0) // ������ ��
	{
		_currReloadDelay = max(0, _currReloadDelay - elapsedTime);
		_attackAni->stop();

		if (_currReloadDelay == 0) // ������ ���� ���
		{
			_currBullet = _maxBullet;
			_reloadAni->start();
		}
	}
	_attackAni->frameUpdate(elapsedTime);
	_reloadAni->frameUpdate(elapsedTime);

	if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		_attackAni->stop();
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
	renderPosHand.x += ((isLeft) ? (_iconImg->getWidth() * 0.1f * 4) : -(_iconImg->getWidth() * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	// �����κ��� ���콺 ���ӱ����� ����
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x += ((isLeft) ? -(_iconImg->getWidth() * 0.2f * 4) : (_iconImg->getWidth() * 0.2f * 4));
	renderPosWeapon.y -= _iconImg->getHeight() * 0.1f * 4;
	float renderDegree = degree;
	if (isLeft) // ������ ���� ����
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

	Vector2 subHandPos = renderPosHand; // ���� �� (��չ���)
	subHandPos.x += _iconImg->getWidth() * 0.4 * 4;
	subHandPos.y += (isLeft) ? (_iconImg->getHeight() * 0.2 * 4) : (_iconImg->getHeight() * -0.2 * 4);
	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	//D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	//D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	//D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));
	
	Vector2 renderPosHand02 = pos;
	renderPosHand02.x += ((isLeft) ? (_iconImg->getWidth() * 0.1f * 4) : -(_iconImg->getWidth() * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand02.y += 30; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	if (_drawEffect) // �߻� ����Ʈ�� �׸���
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // ���� ��ġ�κ���
		//effectPos.x += 5;
		//effectPos.y = renderPosWeapon.y + 15;

		Image* effectImg = IMAGE_MANAGER->findImage("ShootEffect_test");
		Vector2 effectSize = Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4);

		float length = _iconImg->getWidth() * 0.6f * 7; // ���� ���̸�ŭ
		effectPos.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;

		EFFECT_MANAGER->play("L_Effect_Shoot_test", effectPos, effectSize, degree);
	}

	// ������ ���̶�� ������ UI�� �׸���.
	if (_currReloadDelay > 0)
	{
		float ratio = _currReloadDelay / _baseReloadDelay;
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
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currReloadDelay > 0) return; // ���� �߿� ������ ���� ����
	if (_currBullet == 0) // �Ѿ��� ���ٸ�
	{
		if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
		{
			_currReloadDelay = _baseReloadDelay; // ������ ��
		}
		return;
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_iconImg->getWidth() * 0.1f * 4) : -(_iconImg->getWidth() * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 25; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	// �����κ��� ���콺 ���ӱ����� ����
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2 + RANDOM->getFromFloatTo(-PI * 0.02, PI * 0.02);
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	Vector2 shootPos = renderPosHand;
	float length = _iconImg->getWidth() * 0.6f * 6; // ���� ���̸�ŭ
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.05) : (0.05))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.1) : (0.1))) * length;
	Image* _bulletImg = IMAGE_MANAGER->findImage("GunBullet");

	NormalProjectile* projectile = new NormalProjectile;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(_bulletImg->getFrameSize().x * 4, _bulletImg->getFrameSize().y * 3.1f));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("GunBullet", angleRadian, 30 * 50, true, false, 10, true, "", Vector2(), 800);	// �����Ÿ� �߰��߾�� >> Ȳ����

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->critical = 0;
	attackInfo->criticalDamage = 0;
	attackInfo->minDamage = _addStat.minDamage;
	attackInfo->maxDamage = _addStat.maxDamage;
	attackInfo->knockBack = 30;

	player->attack(projectile, attackInfo);
	
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���

	_attackAni->start();
}

void GatlingGun::attack(FloatRect * rect, AttackInfo * info)
{
}

void GatlingGun::attack(FloatCircle * circle, AttackInfo * info)
{
}

void GatlingGun::attack(Projectile * projectile, AttackInfo * info)
{
}

void GatlingGun::reload(Player * player)
{
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
	{
		_currReloadDelay = _baseReloadDelay; // ������ ��
	}
}

void GatlingGun::getHit(Vector2 const position)
{
}

void GatlingGun::equip(Player * player)
{
}

wstring GatlingGun::getBulletUI()
{
	return to_wstring(_currBullet) + L"/" + to_wstring(_maxBullet);
}

float GatlingGun::getBulletRatio()
{
	return _currReloadDelay / _baseReloadDelay;
}
