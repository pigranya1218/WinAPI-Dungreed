#include "GreenBat.h"
#include"NormalProjectile.h"

void GreenBat::init()
{
	_itemCode = 0x03204;
	_iconImg = IMAGE_MANAGER->findImage("GreenBat");
	_price = 600;
	_itemName = L"�ʷ� ����";
	_displayInfos.push_back(L"�ʷ� ���� ��ȯ");
	_displayText = L"\"ī��κ�ϰ� �Ʒ��� ��Ų �ʷ� ����. ���谡�� ������ �����Ѵ�.\"";

	_batPos.x = WINSIZEX / 2;
	_batPos.y = WINSIZEY / 2;

	_baseAttackDelay = 0.1;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
	_drawEffect = false;
	_img = IMAGE_MANAGER->findImage("GreenBatF");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void GreenBat::release()
{
}

void GreenBat::update(Player * player, float const elapsedTime)
{
	if (_batPos.x < _renderPos.x - 600 || _batPos.x > _renderPos.x + 600 || _batPos.y < _renderPos.y - 600 || _batPos.x > _renderPos.x + 600)
	{
		_batPos.x = _renderPos.x;
		_batPos.y = _renderPos.y;
	}
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
	
	_batPos*elapsedTime;
	_renderPos = player->getPosition();
	if (_batPos.x > _renderPos.x + 10)
	{
		_batPos.x -= 500 * elapsedTime;
	}
	else if (_batPos.x <= _renderPos.x)
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

void GreenBat::backRender(Player * player)
{
	
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_batPos), _ani, _direction == DIRECTION::LEFT);
}

void GreenBat::frontRender(Player * player)
{
}

void GreenBat::displayInfo()
{
}

void GreenBat::attack(Player * player)
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
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _batPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _batPos.x)) + PI2;
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
	projectile->setSize(Vector2(110, 110));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 500, true, true, 20, true, "BabyBatBulletFx", Vector2(110, 110), 1,false);
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	_drawEffect = true; // ����Ʈ �׸���
}

void GreenBat::attack(FloatRect * rect, AttackInfo * info)
{
}

void GreenBat::attack(FloatCircle * circle, AttackInfo * info)
{
}

void GreenBat::attack(Projectile * projectile, AttackInfo * info)
{
	
}

void GreenBat::getHit(Vector2 const position)
{
}

void GreenBat::equip(Player* player)
{
}
