#include "babyGreenBat.h"
#include "NormalProjectile.h"
void babyGreenBat::init()
{
	
	_iconImg = IMAGE_MANAGER->findImage("babyGreenBat");
	_itemCode = 0x03100;

	_itemName = L"아기 초록 박쥐";	
	_displayInfos.push_back(L"아기 초록 박쥐 소환");
	_displayText = L"\"길을 잃지 않게 잘 이끌어주게.-카블로비나-\"";

	
	
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
	if (_currAttackDelay > 0) // 공격 딜레이 대기 중
	{
		_currAttackDelay = max(0, _currAttackDelay - elapsedTime);
	}
	else if (_currReloadDelay > 0) // 재장전 중
	{
		_currReloadDelay = max(0, _currReloadDelay - elapsedTime);
		if (_currReloadDelay == 0) // 장전이 끝난 경우
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
	
	if (_currAttackDelay > 0) return; // 공격 쿨타임인 경우 공격을 하지 않음
	if (_currBullet == 0) // 총알이 없다면
	{
		if (_currReloadDelay == 0) // 재장전 중이 아니라면
		{
			_currReloadDelay = _baseReloadDelay; // 재장전 함
		}
		return;
	}

	bool isLeft = (player->getDirection() == DIRECTION::LEFT);
	Vector2 pos = _batPos;

	// 손으로부터 마우스 에임까지의 각도
	float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _batPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _batPos.x)) + PI2;
	if (angleRadian > PI2)
	{
		angleRadian -= PI2;
	}
	NormalProjectile* projectile = new NormalProjectile;
	Vector2 shootPos = pos;
	float length = _img->getWidth() * 0.3f ; // 길이만큼
	shootPos.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	shootPos.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length;
	projectile->setPosition(shootPos);
	projectile->setSize(Vector2(100, 100));
	projectile->setTeam(OBJECT_TEAM::PLAYER);
	projectile->init("BabyBatBulletAt", angleRadian, 500, true, true, 20, true, "BabyBatBulletFx", Vector2(100,100), 0.9,false); 
	AttackInfo* attackInfo = new AttackInfo;
	attackInfo->team = OBJECT_TEAM::PLAYER;	
	player->attack(projectile, attackInfo);
	_currAttackDelay = _baseAttackDelay; // 공격 쿨타임 설정
	_currBullet -= 1; // 탄환 1 줄임
	_drawEffect = true; // 이펙트 그리기

	NormalProjectile* projectile0 = new NormalProjectile;
	Vector2 shootPos0 = pos;
	float length0 = _img->getWidth() * 0.001f; // 길이만큼
	shootPos0.x += cosf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length0;
	shootPos0.y += -sinf(angleRadian + ((isLeft) ? (-0.2) : (0.2))) * length0;
	projectile0->setPosition(Vector2(shootPos0.x, shootPos0.y-15));
	projectile0->setSize(Vector2(100, 100));
	projectile0->setTeam(OBJECT_TEAM::PLAYER);
	projectile0->init("BabyBatBulletAt", angleRadian, 500, true, true, 20, true, "BabyBatBulletFx", Vector2(100, 100), 0.9, false);
	AttackInfo* attackInfo0 = new AttackInfo;
	attackInfo0->team = OBJECT_TEAM::PLAYER;
	player->attack(projectile0, attackInfo0);
	_currAttackDelay = _baseAttackDelay; // 공격 쿨타임 설정
	_currBullet -= 1; // 탄환 1 줄임
	_drawEffect = true; // 이펙트 그리기
	
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
