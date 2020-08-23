#include "stdafx.h"
#include "ShortSpear.h"

void ShortSpear::init()
{
	_iconImg = _img = IMAGE_MANAGER->findImage("ShortSpear");
	_price = 600;
	
	_itemName = L"��â";
	_displayInfos.push_back(L"\"�׽�Ʈ�� ���� ���۵�\"");
	_displayText = L"\"���� �� �ְ� ���۵� ª�� â\"";
	_itemCode = 0x02101; // ��� �Ϲ�

	// �⺻ �����ɼ�
	_addStat.dashDamage = 20;
	_addStat.minDamage = 7;
	_addStat.maxDamage = 10;
	_addStat.attackSpeed = 0.4;

	// private ���� ����
	_attackMove = Vector2(0, 0);
	_currAttackDelay = 0;
	_reverseMove = false;
	_drawEffect = false;
}



void ShortSpear::update(Player* player, float const elapsedTime)
{
	if (_currAttackDelay == 0) return;

	float ratio = elapsedTime / (_adjustStat.attackSpeed * 0.15);
	if (_reverseMove)
	{
		_attackMove.x = max(0, _attackMove.x - abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = max(0, _attackMove.y - abs(-sinf(_attackAngle) * 40 * ratio));
	}
	else
	{
		_attackMove.x = min(abs(cosf(_attackAngle) * 40), _attackMove.x + abs(cosf(_attackAngle) * 40 * ratio));
		_attackMove.y = min(abs(-sinf(_attackAngle) * 40), _attackMove.y + abs((-sinf(_attackAngle)) * 40 * ratio));

		// ��� ��ǵ��� ��� ��������
		player->attack(_attackCircle, _attackInfo);

		if (_currAttackDelay <= _adjustStat.attackSpeed * 0.8)
		{
			_reverseMove = true;
			_drawEffect = true;
			delete _attackCircle;
			delete _attackInfo;
		}
	}

	// ���� ������ ���
	_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
}

void ShortSpear::backRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	Vector2 renderPos = Vector2(pos.x + ((isLeft) ? (-22) : (22)), pos.y + 20);
	FloatRect handRc = rectMakePivot(renderPos, Vector2(5, 5), PIVOT::CENTER);
	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1);
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1, 2.f);
}

void ShortSpear::frontRender(Player* player)
{
	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = player->getPosition();
	
	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 20; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����
	// �����κ��� ���콺 ���ӱ����� ����
	float degree = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) * (180 / PI) + 360;
	if (degree > 360)
	{
		degree -= 360;
	}

	Vector2 renderPosWeapon = renderPosHand;
	renderPosWeapon.x -= ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4));
	
	float renderDegree = degree;
	if (isLeft) // ������ ���� ����
	{
		renderDegree = 180 - degree;
		if (renderDegree < 0) renderDegree += 360;
	}
	renderPosWeapon.x += ((isLeft)?(-_attackMove.x):(_attackMove.x));
	renderPosWeapon.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));
	renderPosHand.x += ((isLeft)?(-_attackMove.x):(_attackMove.x));
	renderPosHand.y += ((degree >= 180) ? (_attackMove.y) : (-_attackMove.y));

	_img->setScale(4);
	_img->setAngle(renderDegree);
	_img->setAnglePos(Vector2(0.35f * _img->getWidth(), 0.5f * _img->getHeight()));
	_img->render(CAMERA->getRelativeV2(renderPosWeapon), isLeft);

	FloatRect handRc = rectMakePivot(renderPosHand, Vector2(5, 5), PIVOT::CENTER);

	D2D_RENDERER->fillRectangle(CAMERA->getRelativeFR(handRc), 210, 188, 181, 1, degree, CAMERA->getRelativeV2(renderPosHand));
	D2D_RENDERER->drawRectangle(CAMERA->getRelativeFR(handRc), 40, 36, 58, 1.f, 2.f, degree, CAMERA->getRelativeV2(renderPosHand));
	
	if (_drawEffect) // ����Ʈ�� �׸���
	{
		_drawEffect = false;
		Vector2 effectPos = renderPosHand; // ���� ��ġ�κ���
		float length = _img->getWidth() * 4 * 0.7; // ���� ���̸�ŭ
		effectPos.x += cosf(degree * (PI / 180)) * length;
		effectPos.y += -sinf(degree * (PI / 180)) * length;
		// D2D_RENDERER->drawRectangle(FloatRect(effectPos, Vector2(10, 10), PIVOT::CENTER), D2DRenderer::DefaultBrush::Black, 1, angle, effectPos);
		EFFECT_MANAGER->play("EFFECT_STAB", effectPos, Vector2(35, 35), degree);
	}
	if (_attackCircle != nullptr)
	{
		_attackCircle->render(true);
	}
}


void ShortSpear::attack(Player* player)
{
	if (_currAttackDelay > 0) return;

	CAMERA->pushShakeEvent(10, 0.1f);

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);

	Vector2 pos = player->getPosition();
	Vector2 renderPosHand = pos;
	renderPosHand.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	renderPosHand.y += 20; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����
	// �����κ��� ���콺 ���ӱ����� ����
	float angle = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - renderPosHand.y), (CAMERA->getAbsoluteX(_ptMouse.x) - renderPosHand.x)) + PI2;
	if (angle > PI2)
	{
		angle -= PI2;
	}
	_attackAngle = angle;

	_reverseMove = false;
	_currAttackDelay = _adjustStat.attackSpeed;
	Vector2 originPos = player->getPosition();
	originPos.x += ((isLeft) ? (_img->getWidth() * 0.15f * 4) : -(_img->getWidth() * 0.15f * 4)); // ���� ��ġ�� ������ ȸ�� �߽���
	originPos.y += 20; // �÷��̾��� �������κ��� ���⸦ ��� �ִ� ����
	float attackRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - originPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - originPos.x));
	if (attackRadian < 0)
	{
		attackRadian += PI2;
	}
	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime()); // ������ �ڵ�� ���� �ð��� Concat�Ͽ� ���� ���̵� ���ϱ� ���� ���� �ڵ带 ������

	SOUND_MANAGER->stop("SOUND_generalAttack");
	SOUND_MANAGER->play("SOUND_generalAttack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));

	_attackCircle = new FloatCircle;
	_attackCircle->origin = originPos;
	_attackCircle->size = 150;
	_attackCircle->startRadian = attackRadian - PI * 0.05;
	_attackCircle->endRadian = attackRadian + PI * 0.05;
	_attackInfo = new AttackInfo;
	_attackInfo->team = OBJECT_TEAM::PLAYER;
	_attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	_attackInfo->critical = 0;
	_attackInfo->criticalDamage = 0;
	_attackInfo->minDamage = _addStat.minDamage;
	_attackInfo->maxDamage = _addStat.maxDamage;
	_attackInfo->knockBack = 5;
}



void ShortSpear::equip(Player* player)
{
	PlayerStat stat = player->getCurrStat();
	_adjustStat = _addStat;
	// �÷��̾��� ���ݼӵ��� 30�̶�� ���� ���ݼӵ��� (100 - 30)%�� ������ = 70%
	_adjustStat.attackSpeed = _addStat.attackSpeed * ((100 - stat.attackSpeed) / 100);
}
