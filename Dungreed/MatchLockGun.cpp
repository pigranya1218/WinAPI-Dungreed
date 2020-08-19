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
	_itemName = L"ȭ����";
	_displayText = L"\"�� ���� ����� �� ���� ��\"";

	// �⺻ �����ɼ�
	_addStat.minDamage = 30;
	_addStat.maxDamage = 40;
	_addStat.attackSpeed = 1;
	_addStat.reloadSpeed = 1;

	// private ���� ����
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
	if (_currAttackDelay > 0) // ���� ������ ��� ��
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	else if (_currReloadDelay > 0) // ������ ��
	{
		_currReloadDelay = max(0, _currReloadDelay - elapsedTime);
		if (_currReloadDelay == 0) // ������ ���� ���
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
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.1f * 4) : -(_img->getWidth() * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����
	
	// �����κ��� ���콺 ���ӱ����� ����
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x += ((isLeft) ? -(_img->getWidth() * 0.2f * 4) : (_img->getWidth() * 0.2f * 4));
	renderPosWeapon.y -= _img->getHeight() * 0.1f * 4;
	float renderDegree = degree;
	if (isLeft) // ������ ���� ����
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(Vector2(0.3f * _img->getWidth(), 0.6f * _img->getHeight()));
	_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);

	Vector2 subHandPos = renderPosHand; // ���� �� (��չ���)
	subHandPos.x +=  _img->getWidth() * 0.4 * 4;
	subHandPos.y += (isLeft)?(_img->getHeight() * 0.2 * 4):(_img->getHeight() * -0.2 * 4);
	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	if (_drawEffect) // ����Ʈ�� �׸���
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // ���� ��ġ�κ���

		/*Vector2 effectPos;
		effectPos.x = (isLeft) ? (renderPosHand.x + 18) : (renderPosHand.x - 18);
		effectPos.y = renderPosHand.y;*/

		Vector2 effectSize = Vector2(220, 220);
		float length = _img->getWidth() * 0.6f * 4; // ���� ���̸�ŭ
		effectPos.x += cosf(degree * (PI / 180) + ((isLeft)?(-0.2):(0.2))) * length;
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;

		/*float changeX = cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		effectPos.x += (isLeft) ? (changeX + 18) : (changeX - 18);
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;*/

		EFFECT_MANAGER->play("L_Effect_HecateSmoke", effectPos, effectSize, degree);

		Image* effectImg = IMAGE_MANAGER->findImage("ShootEffect");
		Vector2 effectSize02 = Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4);

		float length02 = _iconImg->getWidth() * 0.6f * 3; // ���� ���̸�ŭ
		effectPos.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length02;
		effectPos.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length02;

		EFFECT_MANAGER->play("L_Effect_Shoot", effectPos, effectSize02, degree);
	}

	// ������ ���̶�� ������ UI�� �׸���.
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
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currReloadDelay > 0) return; // ���� �߿� ������ ���� ����
	if (_currBullet == 0) // �Ѿ��� ���ٸ�
	{
		if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
		{
			_currReloadDelay = _adjustStat.reloadSpeed; // ������ ��
		}
		return;
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.1f * 4) : -(_img->getWidth() * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	// �����κ��� ���콺 ���ӱ����� ����
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	Vector2 shootPos = renderPosHand;
	float length = _img->getWidth() * 0.6f * 4; // ���� ���̸�ŭ
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	Image* _bulletImg = IMAGE_MANAGER->findImage("GunBullet");

	projectile = new NormalProjectile;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(_bulletImg->getFrameSize().x * 4, _bulletImg->getFrameSize().y * 4));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("GunBullet", angleRadian, 30 * 50, true, false, 10, false, "", Vector2(), 800);	// �����Ÿ� �߰��߾�� >> Ȳ����

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
	_currAttackDelay = _adjustStat.attackSpeed; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���
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
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
	{
		_currReloadDelay = _adjustStat.reloadSpeed; // ������ ��
	}
}

void MatchLockGun::getHit(Vector2 const position)
{
}

void MatchLockGun::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
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
