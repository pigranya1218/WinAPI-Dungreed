#include "OakBow.h"
#include "NormalProjectile.h"

void OakBow::init()
{
	_iconImg = IMAGE_MANAGER->findImage("OakBow");
	_img = IMAGE_MANAGER->findImage("OakBowAni");

	_itemCode = 0x02161;
	_itemName = L"�������� Ȱ";
	_displayText = L"\"�ܴ��ؼ� ������ �� �� ���� ���� �� �����ϴ�.\"";

	// �⺻ �����ɼ�
	
	_addStat.attackSpeed = 1;
	_addStat.reloadSpeed = 0.1;

	_price = 360;

	// private ���� ����
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

	if (_ani->isPlay())
	{
		_ani->frameUpdate(elapsedTime);
	}

	//if (_ani->getPlayIndex() == 3)
	//{
	//	_effectCount++;
	//	if (_effectCount == 20)
	//	{
	//		_drawEffect = true;						// ����Ʈ �׸���
	//	}
	//	else
	//	{
	//		_drawEffect = false;
	//	}
	//}

	renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getFrameSize().x * 0.1f * 4) : -(_img->getFrameSize().y * 0.1f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 15; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����

	subHandPos = renderPosHand; // ���� �� (��չ���) ������
	subHandPos.x += _img->getFrameSize().x * 0.35 * 3;
	subHandPos.y += (isLeft) ? (_img->getFrameSize().y * -0.1 * 4) : (_img->getFrameSize().y * 0.1 * 4);

	// �����κ��� ���콺 ���ӱ����� ����
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	//����Ʈ ������
	_effectAngleRadianValue = angleRadian;

	renderPosWeapon = (isLeft) ? Vector2(renderPosHand.x - 9.0f, renderPosHand.y) : Vector2(renderPosHand.x + 9.0f, renderPosHand.y);

	anglePos = Vector2(0.35f * _img->getFrameSize().x, 0.5f * _img->getFrameSize().y);

	if (_isAttack)
	{
		//_ani->setFPS(1);
		//_ani->setPlayFrame(0, 4, false);
		//_ani->start();

		//���� ����
		if (KEY_MANAGER->isOnceKeyUp(CONFIG_MANAGER->getKey(ACTION_TYPE::ATTACK)))
		{
			if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
			if (_currBullet == 0) // �Ѿ��� ���ٸ�
			{
				if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
				{
					_currReloadDelay = _adjustStat.reloadSpeed; // ������ ��
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

			float length = _img->getFrameSize().x * 0.5f * 3; // ���� ���̸�ŭ

			Vector2 arrowPos = renderPosWeapon;
			arrowPos.x = (isLeft) ? (renderPosWeapon.x + anglePos.x + 5) : (renderPosWeapon.x + anglePos.x - 15);
			//arrowPos.y = (isLeft) ? (renderPosWeapon.y + 10) : (renderPosWeapon.y);
			
			Image* effectImg = IMAGE_MANAGER->findImage("ArrowHitEffect");

			NormalProjectile* projectile = new NormalProjectile;
			projectile->setPosition(arrowPos);
			projectile->setSize(Vector2(80, 15));
			projectile->setTeam(OBJECT_TEAM::PLAYER);
			projectile->init("Arrow00", angleRadian, 30 * 50, false, false, 20, true, "L_Effect_ArrowHit", Vector2(effectImg->getFrameSize().x * 4, effectImg->getFrameSize().y * 4), 800);

			string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

			AttackInfo* attackInfo = new AttackInfo;
			attackInfo->team = OBJECT_TEAM::PLAYER;
			attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
			attackInfo->critical = 0;
			attackInfo->criticalDamage = 0;
			attackInfo->minDamage = _addStat.minDamage;
			attackInfo->maxDamage = _addStat.maxDamage;
			attackInfo->knockBack = 0;

			player->attack(projectile, attackInfo);
			_currAttackDelay = _adjustStat.attackSpeed;	// ���� ��Ÿ�� ����
			_currBullet -= 1;						// źȯ 1 ����

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

	// �����κ��� ���콺 ���ӱ����� ����
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	float renderDegree = degree;
	if (isLeft) // ������ ���� ����
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

	//�� �׸��� �����ؾ��ϴ�...��...
	Vector2 renderSunHandPos = subHandPos;

	FloatRect subhandRc = rectMakePivot(subHandPos, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(subhandRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(subhandRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1.f, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));

	//����Ʈ
	if (_effectCount == 1)
	{
		Vector2 effectPos01 = renderPosHand; // ���� ��ġ�κ���

		Vector2 effectSize01 = Vector2(50, 50);
		float length = _img->getFrameSize().x * 0.6f * 4; // ���� ���̸�ŭ
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
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currBullet == 0) // �Ѿ��� ���ٸ�
	{
		if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
		{
			_currReloadDelay = _adjustStat.reloadSpeed; // ������ ��
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
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
	_adjustStat.reloadSpeed = _addStat.reloadSpeed * ((100 - stat.reloadSpeed) / 100);
}

float OakBow::getBulletRatio()
{
	return _currReloadDelay / _adjustStat.reloadSpeed;
}
