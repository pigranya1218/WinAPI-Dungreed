#include "stdafx.h"
#include "ShopNpc.h"
#include "UIManager.h"

void ShopNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::SHOP;
	_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_SHOP");
	_miniMapIcon = nullptr;

	_img = IMAGE_MANAGER->findImage("NPC_SHOP");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(10);
	_ani->start();

	_position = pos;
	_direction = direction;
	_size = Vector2(50, 190);
	_active = true;

	_name = "크록";
	_bodyDialogue = "가나다라마바사아자차카타파하";
	_selectDialogues.push_back("상점");

	_isActiveInteraction = false;
	_isClose = false;
}

void ShopNpc::release()
{
	_ani->release();
	delete _ani;
}

void ShopNpc::update(float timeElapsed)
{
	Npc::update(timeElapsed);

	_ani->frameUpdate(timeElapsed);
}

void ShopNpc::interaction()
{
	_uiMgr->setDialogue(this);
	_isActiveInteraction = true;
}

void ShopNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	Npc::render();
}
