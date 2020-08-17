#include "GreenDadBat.h"
#include "stdafx.h"
#include "NormalProjectile.h"

void GreenDadBat::init()
{
	_itemCode = 0x03305;
	_iconImg = IMAGE_MANAGER->findImage("GreenDadBat");

	_price = 3500;

	_batPos.x = WINSIZEX / 2;
	_batPos.y = WINSIZEY / 2;
	
	_img = IMAGE_MANAGER->findImage("GreenDadBatF");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(9);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);

	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
	_drawEffect = false;
}

void GreenDadBat::release()
{
}

void GreenDadBat::update(Player * player, float const elapsedTime)
{
	_direction = player->getDirection();

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
	
	_renderPos = player->getPosition();
	if (_batPos.x > _renderPos.x - 70)
	{
		_batPos.x -= 500 * elapsedTime;
	}
	else if (_batPos.x <= _renderPos.x - 90)
	{
		_batPos.x += 500 * elapsedTime;
	}
	if (_batPos.y > _renderPos.y + 5 && _batPos.y > _renderPos.y)
	{
		_batPos.y -= 500 * elapsedTime;
	}
	else if (_batPos.y < _renderPos.y - 5)
	{
		_batPos.y += 500 * elapsedTime;
	}
	_ani->frameUpdate(elapsedTime);
	
}

void GreenDadBat::backRender(Player * player)
{
	
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_batPos), _ani, _direction == DIRECTION::LEFT);


}

void GreenDadBat::frontRender(Player * player)
{
}

void GreenDadBat::displayInfo()
{
}

void GreenDadBat::attack(Player * player)
{
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currBullet == 0) // �Ѿ��� ���ٸ�
	{
		if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
		{
			_currReloadDelay = _baseReloadDelay; // ������ ��
		}
		return;
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = _batPos;

	// �����κ��� ���콺 ���ӱ����� ����
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _batPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _batPos .x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	NormalProjectile* projectile = new NormalProjectile;
	Vector2 shootPos = pos;
	float length = _img->getWidth() * 0.6f * 0.1; // ���� ���̸�ŭ
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(170, 170));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 600, true, true, 20, true, "BabyBatBulletFx", Vector2(200, 200), 700); // �����Ÿ� �߰��߾�� >> Ȳ����
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���
}

void GreenDadBat::attack(FloatRect * rect, AttackInfo * info)
{
}

void GreenDadBat::attack(FloatCircle * circle, AttackInfo * info)
{
}

void GreenDadBat::attack(Projectile * projectile, AttackInfo * info)
{
}

void GreenDadBat::getHit(Vector2 const position)
{
}

void GreenDadBat::equip(Player* player)
{
}
