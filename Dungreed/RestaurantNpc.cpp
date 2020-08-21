#include "stdafx.h"
#include "RestaurantNpc.h"
#include "NpcManager.h"
#include "UIManager.h"

void RestaurantNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::RESTAURANT;

	_img = IMAGE_MANAGER->findImage("NPC_RESTAURANT");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(10);
	_ani->start();

	_position = pos;
	_direction = direction;
	_size = Vector2(50, 100);
	_active = true;

	_name = "호레리카";
	_bodyDialogue = "가나다라마바사아자차카타파하";
	_selectDialogues.push_back("식당");

	_isActiveInteraction = false;
	_isClose = false;
}

void RestaurantNpc::release()
{
	_ani->release();
	delete _ani;
}

void RestaurantNpc::update(float timeElapsed)
{
	Npc::update(timeElapsed);

	_ani->frameUpdate(timeElapsed);
}

void RestaurantNpc::interaction()
{
	_uiMgr->setDialogue(this);
	_isActiveInteraction = true;
}

void RestaurantNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	Npc::render();
}
