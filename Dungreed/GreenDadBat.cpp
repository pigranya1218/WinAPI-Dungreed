#include "GreenDadBat.h"
#include "stdafx.h"
#include "NormalProjectile.h"

void GreenDadBat::init()
{
	_itemCode = 0x03305;
	_iconImg = IMAGE_MANAGER->findImage("GreenDadBat");
	_itemName = L"�ƺ� �ʷ� ����";
	_displayInfos.push_back(L"�ƺ� �ʷ� ���� ��ȯ");
	_displayText = L"\"���� �� ���� �ʾ� �Ʒ��ϱⰡ ���� �ʴ���""\"-ī��κ�";
	_price = 3500;

	_batPos.x = WINSIZEX / 2;
	_batPos.y = WINSIZEY / 2;
	
	_img = IMAGE_MANAGER->findImage("GreenDadBatF");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(13);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);

	_baseAttackDelay = 0.8;
	_currAttackDelay = 0;
	_maxBullet = 1;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
	
}

void GreenDadBat::release()
{
}

void GreenDadBat::update(Player * player, float const elapsedTime)
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
	else
	{
		SOUND_MANAGER->stop("GiantBat/Attack");
		SOUND_MANAGER->play("GiantBat/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
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
	projectile->setTeam(OBJECT_TEAM::PLAYER);		
	projectile->init("BabyBatBulletAt", "DadBatBulletFX", Vector2(190, 190), Vector2(70, 70), Vector2(190, 190), Vector2(900, 900), 1, angleRadian, true, true, 20, false, false, true, false);	// �Լ� �μ��� �ٲ����� >> Ȯ�����ּ���

	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());

	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;
	attackInfo->madeByWeapon = false; 
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
	attackInfo->maxDamage = 5;
	attackInfo->minDamage = 3;
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
	_currBullet -= 1; // źȯ 1 ����
	
}
