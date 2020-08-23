#include "babyGreenBat.h"
#include "NormalProjectile.h"
void babyGreenBat::init()
{
	
	_iconImg = IMAGE_MANAGER->findImage("babyGreenBat");
	_itemCode = 0x03100;

	_itemName = L"�Ʊ� �ʷ� ����";	
	_displayInfos.push_back(L"�Ʊ� �ʷ� ���� ��ȯ");
	_displayText = L"\"���� ���� �ʰ� �� �̲����ְ�.-ī��κ�-\"";

	
	
	_price = 600;
	
	_batPos.x = WINSIZEX / 2;
	_batPos.y = WINSIZEY / 2;

	_img = IMAGE_MANAGER->findImage("babyGreenBatF");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(18);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);

	_baseAttackDelay = 0.6;
	_currAttackDelay = 0;
	_maxBullet = 2;
	_currBullet = _maxBullet;
	_baseReloadDelay = 0.15;
	_currReloadDelay = 0;
}

void babyGreenBat::release()
{
	
}

void babyGreenBat::update(Player* player, float const elapsedTime)
{
	if (_batPos.x < _renderPos.x - 600 || _batPos.x > _renderPos.x + 600 || _batPos.y < _renderPos.y - 600 || _batPos.x > _renderPos.x + 600)
	{
		_batPos.x = _renderPos.x;
		_batPos.y = _renderPos.y;
	}
	_renderPos = player->getPosition();
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
	
	if (_batPos.x > _renderPos.x + 60)
	{
		_batPos.x -= 500*elapsedTime;
	}
	else if (_batPos.x <= _renderPos.x + 10)
	{
		_batPos.x += 500 * elapsedTime;
	}
	if (_batPos.y > _renderPos.y )
	{
		_batPos.y -= 500 * elapsedTime;
	}
	else if (_batPos.y < _renderPos.y - 7 && _batPos.y <= _renderPos.y-2)
	{
		_batPos.y += 500 * elapsedTime;
	}

	
	
	_ani->frameUpdate(elapsedTime);
	

}

void babyGreenBat::frontRender(Player* player)
{
}

void babyGreenBat::backRender(Player* player)
{
	
	
	_img->setScale(3);
	_img->aniRender(CAMERA->getRelativeV2(_batPos), _ani, _direction == DIRECTION::LEFT);
}



void babyGreenBat::attack(Player* player)
{
	
	if (_currAttackDelay > 0) return; // ���� ��Ÿ���� ��� ������ ���� ����
	if (_currBullet == 0) // �Ѿ��� ���ٸ�
	{
		SOUND_MANAGER->stop("Bat/Attack");
		SOUND_MANAGER->play("Bat/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
		if (_currReloadDelay == 0) // ������ ���� �ƴ϶��
		{
			_currReloadDelay = _baseReloadDelay; // ������ ��
		}
		return;
	}
	else
	{
		SOUND_MANAGER->stop("Bat/Attack");
		SOUND_MANAGER->play("Bat/Attack", CONFIG_MANAGER->getVolume(SOUND_TYPE::EFFECT));
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
	float length = _img->getWidth() * 0.3f ; // ���̸�ŭ
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(75, 75));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", "BabyBatBulletFx", Vector2(100, 100), Vector2(100, 100), Vector2(100, 100),Vector2(500, 500), 0.9, angleRadian, true, true, 20, false, false, true, false);


	string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;	
	attackInfo->madeByWeapon = false;
	attackInfo->attackID = TTYONE_UTIL::getHash(attackCode + "1");
	attackInfo->maxDamage = 1;
	attackInfo->minDamage = 2;
	player->attack(projectile, attackInfo);

	NormalProjectile* projectile0 = new NormalProjectile;
	Vector2 shootPos0 = pos;
	float length0 = _img->getWidth() * 0.001f; // ���̸�ŭ
	shootPos0.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length0;
	shootPos0.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length0;
	projectile0->setPosition(Vector2(shootPos0.x, shootPos0.y-15));
	projectile0->setSize(Vector2(75, 75));
	projectile0->setTeam(OBJECT_TEAM::PLAYER);
	projectile0->init("BabyBatBulletAt", "BabyBatBulletFx", Vector2(100, 100), Vector2(100, 100), Vector2(100, 100), Vector2(500, 500), 0.9, angleRadian, true, true, 20, false, false, true, false);

	AttackInfo* attackInfo0 = new AttackInfo;
	attackInfo0->team = OBJECT_TEAM::PLAYER;
	attackInfo0->madeByWeapon = false; 
	attackInfo0->attackID = TTYONE_UTIL::getHash(attackCode + "2");
	attackInfo0->maxDamage = 1;
	attackInfo0->minDamage = 2;
	player->attack(projectile0, attackInfo0);
	_currAttackDelay = _baseAttackDelay; // ���� ��Ÿ�� ����
}
