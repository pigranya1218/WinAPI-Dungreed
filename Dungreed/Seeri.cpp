#include "Seeri.h"

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
	_ani->frameUpdate(elapsedTime);
	
}

void Seeri::backRender(Player * player)
{
	_renderPos.x = _renderPos.x - 100;
	_img->setScale(3);
	_img->aniRender(CAMERA->getRelativeV2(_renderPos), _ani, true);
}

void Seeri::frontRender(Player * player)
{
}

void Seeri::attack(Player * player)
{
}
