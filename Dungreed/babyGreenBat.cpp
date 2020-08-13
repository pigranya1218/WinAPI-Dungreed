#include "babyGreenBat.h"
#include "NormalProjectile.h"
void babyGreenBat::init()
{
	_type = ITEM_TYPE::ACC;
	_rank = ITEM_RANK::NORMAL;
	_iconImg = IMAGE_MANAGER->findImage("babyGreenBat");

	_price = 600;
	
	batPos.x = WINSIZEX / 2;
	batPos.y = WINSIZEY / 2;

	_img = IMAGE_MANAGER->findImage("babyGreenBatF");
	_ani = new Animation;
	_ani->start();

	_baseAttackDelay = 0.2;
	_currAttackDelay = 0;
	_maxBullet = 2;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
	_drawEffect = false;
}

void babyGreenBat::release()
{
	
}

void babyGreenBat::update(Player* player, float const elapsedTime)
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
	
	if (_ptMouse.x < renderPos.x)
	{
		_direction = DIRECTION::LEFT;

	}
	else
	{
		_direction = DIRECTION::RIGHT;

	}
	_ani->frameUpdate(elapsedTime);
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(14);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);

}

void babyGreenBat::frontRender(Player* player)
{
}

void babyGreenBat::backRender(Player* player)
{
	
	renderPos = player->getPosition();
	if (batPos.x > renderPos.x + 60)
	{
		batPos.x -= 6;
	}
	else if (batPos.x <= renderPos.x + 10)
	{
		batPos.x += 6;
	}
	if (batPos.y > renderPos.y + 5 && batPos.y > renderPos.y)
	{
		batPos.y -= 7;
	}
	else if (batPos.y < renderPos.y - 5 && batPos.y <= renderPos.y)
	{
		batPos.y += 8;
	}	
	_img->setScale(3);
	_img->aniRender(Vector2(batPos), _ani, _direction == DIRECTION::LEFT);
}


void babyGreenBat::displayInfo()
{
}

void babyGreenBat::attack(Player* player)
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
	Vector2 pos = batPos;	

	// �����κ��� ���콺 ���ӱ����� ����
	float angleRadian = atan2f(-(_ptMouse.y - batPos.y), (_ptMouse.x - batPos.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}

	NormalProjectile* projectile = new NormalProjectile;
	Vector2 shootPos = pos;
	float length = _img->getWidth() * 0.3f ; // ���̸�ŭ
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(100, 100));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 10, true, true, 20, false, "BabyBatBulletFx", Vector2(100,100));
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;	
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���

	NormalProjectile* projectile0 = new NormalProjectile;
	Vector2 shootPos0 = pos;
	float length0 = _img->getWidth() * 0.001f; // ���̸�ŭ
	shootPos0.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length0;
	shootPos0.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length0;
	projectile0->setPosition(Vector2(shootPos0.x, shootPos0.y-15));
	projectile0->setSize(Vector2(100, 100));
	projectile0->setTeam(OBJECT_TEAM::PLAYER);
	projectile0->init("BabyBatBulletAt", angleRadian, 10, true, true, 20, false, "BabyBatBulletFx", Vector2(100, 100));
	AttackInfo* attackInfo0 = new AttackInfo;
	attackInfo0->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile0, attackInfo0);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���
	
}

void babyGreenBat::attack(FloatRect * rect, AttackInfo * info)
{
	
}

void babyGreenBat::attack(FloatCircle * circle, AttackInfo * info)
{
}

void babyGreenBat::attack(Projectile * projectile, AttackInfo * info)
{
}

void babyGreenBat::getHit(Vector2 const position)
{
}

PlayerStat babyGreenBat::equip()
{
	return PlayerStat();
}
