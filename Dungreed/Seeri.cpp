#include "Seeri.h"
#include "SeeriProjectile.h"
void Seeri::init()
{
	_iconImg = IMAGE_MANAGER->findImage("Seeri");
	_itemCode = 0x03313;

	_itemName = L"SEERI - 전투 도우미";
	_displayInfos.push_back(L"유도 미사일 발사");
	_displayText = L"\"못생긴 것을 없애주고 싶은 마음을 총알로 만들어주는, 차가운 기계 인형\"";

	_addStat.power = 10;
	_addStat.criticalChance = 5;

	_price = 600;
	_Delay = 4.0;
	_img = IMAGE_MANAGER->findImage("Seeri0");
	_ani = new Animation;
	_ani->start();
	_ani->init(_img->getWidth(), _img->getHeight(),
		_img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(9);
	_ani->setPlayFrame(0, _img->getMaxFrameX(), false, true);
}

void Seeri::release()
{
}

void Seeri::update(Player * player, float const elapsedTime)
{
	
	_renderPos = player->getPosition();
	_direction = player->getDirection();
	Vector2 _enemy = player->getEnemyPos(Vector2());
	_ani->frameUpdate(elapsedTime);
	

	

	if (_Delay > 0)
	{
		_Delay = max(0, _Delay - elapsedTime);
	}
	if (_Delay == 0)
	{
		_Delay = 4.0;

		float angleRadian = atan2f(-(CAMERA->getAbsoluteY(_ptMouse.y) - _renderPos.y), (CAMERA->getAbsoluteX(_ptMouse.x) - _renderPos.x)) + PI2;
		if (angleRadian > PI2)
		{
			angleRadian -= PI2;
		}
		SeeriProjectile* projectile = new SeeriProjectile;
		projectile->setPosition(_renderPos);
		projectile->setTeam(OBJECT_TEAM::PLAYER);
		projectile->init("SeeriBullet", "BombPouch2", Vector2(40, 22), Vector2(25, 25), Vector2(80, 80), Vector2(60 * 10, 60 * 10), 10, _renderPos.y, false, false, 10, true, false, false, false, true);	// 함수 인수가 바뀌었어요 >> 확인해주세요	
		string attackCode = to_string(_itemCode) + to_string(TIME_MANAGER->getWorldTime());
		AttackInfo* attackInfo = new AttackInfo;
		attackInfo->team = OBJECT_TEAM::PLAYER;
		attackInfo->madeByWeapon = false;
		attackInfo->attackID = TTYONE_UTIL::getHash(attackCode);
		attackInfo->maxDamage = 5;
		attackInfo->minDamage = 3;
		player->attack(projectile, attackInfo);
	}
	
}

void Seeri::backRender(Player * player)
{
	_renderPos.x = _renderPos.x - 100;
	_img->setScale(3);
	_img->aniRender(CAMERA->getRelativeV2(_renderPos), _ani, _direction == DIRECTION::RIGHT);
}

void Seeri::frontRender(Player * player)
{
}

void Seeri::attack(Player * player)
{
}
