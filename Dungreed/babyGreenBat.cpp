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
	projectile->setSize(Vector2(100, 100));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 500, true, true, 20, true, "BabyBatBulletFx", Vector2(100,100), 0.9,false); 
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
	projectile0->init("BabyBatBulletAt", angleRadian, 500, true, true, 20, true, "BabyBatBulletFx", Vector2(100, 100), 0.9, false);
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

void babyGreenBat::equip(Player* player)
{
	
}
