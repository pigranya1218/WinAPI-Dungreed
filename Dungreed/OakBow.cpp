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

	// private ���� ����
	_minDamage = 12;
	_maxDamage = 18;
	_baseAttackDelay = 0.5;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 3;
	_currReloadDelay = 0;
	_drawEffect = false;
	_isAttack = false;


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
		}
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	// �����κ��� ���콺 ���ӱ����� ����
	float angleRadian = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	if (_ani->isPlay())
	{
		_ani->frameUpdate(elapsedTime);
	}

	//���� ����
	if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		/*if (_ani->getPlayIndex() >= 5)
		{
			_ani->stop();
		}
		else
		{
			_ani->stop();
		}*/

		_ani->setFPS(6);
		_ani->setPlayFrame(4, 6, false);
		_ani->start();

		if (_ani->getPlayIndex() >= 5)
		{
			_ani->stop();
		}

		NormalProjectile* projectile = new NormalProjectile;
		Vector2 shootPos = renderPosHand;
		float length = _img->getFrameSize().x * 0.6f * 4; // ���� ���̸�ŭ
		shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
		shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
		projectile->setPosition(shootPos);
		projectile->setSize(Vector2(80, 15));
		projectile->setTeam(OBJECT_TEAM::PLAYER);
		projectile->init("Arrow00", angleRadian, 30, false, false, 20, false, "", Vector2());

		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		player->attack(projectile, attackInfo);
		_currAttackDelay = _baseAttackDelay;	// ���� ��Ÿ�� ����
		_currBullet -= 1;						// źȯ 1 ����

		if (_isAttack)
		{
			_isAttack = false;
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

	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	// �����κ��� ���콺 ���ӱ����� ����
	float degree = atan2f(-(_ptMouse.y - renderPosHand.y), (_ptMouse.x - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x += ((isLeft) ? -(_img->getFrameSize().x * 0.2f * 4) : (_img->getFrameSize().y * 0.2f * 4));
	renderPosWeapon.y -= _img->getFrameSize().y * 0.1f * 4;
	float renderDegree = degree;
	if (isLeft) // ������ ���� ����
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(Vector2(0.3f * _img->getFrameSize().x, 0.6f * _img->getFrameSize().y));
	_img->aniRender(renderPosWeapon, _ani, isLeft);

	//if (!_isAttack)
	//{
	//	
	//}

	//if (_isAttack)
	//{
	//	_frameImg->setScale(4);
	//	_frameImg->setAngle(renderDegree);
	//	_frameImg->setAnglePos(Vector2(0.3f * _frameImg->getFrameSize().x, 0.6f * _frameImg->getFrameSize().y));
	//	_frameImg->aniRender(renderPosWeapon, _ani, isLeft);

	//	
	//}

	

	Vector2 subHandPos = renderPosHand; // ���� �� (��չ���)
	subHandPos.x += _img->getFrameSize().x * 0.4 * 4;
	subHandPos.y += (isLeft) ? (_img->getFrameSize().y * 0.2 * 4) : (_img->getFrameSize().y * -0.2 * 4);
	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->drawRectangle(subhandRc, 40, 36, 58, 1.f, 6.f, degree, renderPosHand);
	D2D_RENDERER->fillRectangle(subhandRc, 210, 188, 181, 1.f, degree, renderPosHand);

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->drawRectangle(handRc, 40, 36, 58, 1.f, 6.f, degree, renderPosHand);
	D2D_RENDERER->fillRectangle(handRc, 210, 188, 181, 1.f, degree, renderPosHand);

	if (_drawEffect)
	{
		_drawEffect = false;

		Vector2 effectPos01 = renderPosHand; // ���� ��ġ�κ���

		Vector2 effectSize01 = Vector2(220, 220);
		float length = _img->getFrameSize().x * 0.6f * 4; // ���� ���̸�ŭ
		effectPos01.x += cosf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		effectPos01.y += -sinf(degree * (PI / 180) + ((isLeft) ? (-0.2) : (0.2))) * length;
		EFFECT_MANAGER->play("L_Effect_Charge", effectPos01, effectSize01, degree);
	}
}

void OakBow::displayInfo()
{
}

void OakBow::attack(Player * player)
{
	_ani->setFPS(6);
	_ani->setPlayFrame(0, 4, false);
	_ani->start();

	if (_ani->getPlayIndex() >= 3)
	{
		_drawEffect = true;						// ����Ʈ �׸���
	}

	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currBullet == 0) // �Ѿ��� ���ٸ�
	{
		if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
		{
			_currReloadDelay = _baseReloadDelay; // ������ ��
		}
		return;
	}

	
	
	if (!_isAttack)
	{
		_isAttack = true;
	}

	/*if (KEY_MANAGER->isStayKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
	{
		if (_ani->getPlayIndex() >= 3)
		{
			_ani->pause();
		}
	}*/

	
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

PlayerStat OakBow::equip()
{
	return PlayerStat();
}
