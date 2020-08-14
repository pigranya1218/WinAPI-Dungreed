#include "GreenMomBat.h"
#include "stdafx.h"
#include "NormalProjectile.h"
void GreenMomBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::HIGH;
	_iconImg = IMAGE_MANAGER->findImage("GreenMomBat");

	_price = 3500;


	_batPos.x = WINSIZEX / 2;
	_batPos.y = WINSIZEY / 2;
	_baseAttackDelay = 0.4;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
	_drawEffect = false;
	_img = IMAGE_MANAGER->findImage("GreenMomBatF");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(11);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void GreenMomBat::release()
{
}

void GreenMomBat::update(Player * player, float const elapsedTime)
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
	if (_ptMouse.x < _renderPos.x)
	{
		_direction = DIRECTION::LEFT;

	}
	else
	{
		_direction = DIRECTION::RIGHT;

	}
	_renderPos = player->getPosition();
	if (_batPos.x > _renderPos.x + 80)
	{
		_batPos.x -= 500 * elapsedTime;
	}
	else if (_batPos.x <= _renderPos.x + 60)
	{
		_batPos.x += 500 * elapsedTime;
	}
	if (_batPos.y > _renderPos.y - 70)
	{
		_batPos.y -= 500 * elapsedTime;
	}
	else if (_batPos.y < _renderPos.y - 80 && _batPos.y <= _renderPos.y)
	{
		_batPos.y += 500 * elapsedTime;
	}
	_ani->frameUpdate(elapsedTime);
	
}

void GreenMomBat::backRender(Player * player)
{

	
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_batPos), _ani, _direction == DIRECTION::LEFT);
}

void GreenMomBat::frontRender(Player * player)
{
}

void GreenMomBat::displayInfo()
{
}

void GreenMomBat::attack(Player * player)
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
	float angleRadian = atan2f(-(_ptMouse.y - _batPos.y), (_ptMouse.x - _batPos.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	NormalProjectile* projectile = new NormalProjectile;
	Vector2 shootPos = pos;
	float length = _img->getWidth() * 0.1f; // ���̸�ŭ
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(170, 120));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 18, true, true, 18, false, "BabyBatBulletFx", Vector2(170, 170));
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���
}

void GreenMomBat::attack(FloatRect * rect, AttackInfo * info)
{
}

void GreenMomBat::attack(FloatCircle * circle, AttackInfo * info)
{
}

void GreenMomBat::attack(Projectile * projectile, AttackInfo * info)
{
}

void GreenMomBat::getHit(Vector2 const position)
{
}

void GreenMomBat::equip(Player* player)
{
}
