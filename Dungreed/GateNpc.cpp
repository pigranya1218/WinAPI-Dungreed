#include "GateNpc.h"
#include "UIManager.h"

void GateNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::GATE;
	_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_WORM");

	_img = IMAGE_MANAGER->findImage("NPC_GATE_IDLE");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(10);
	_ani->start();

	_position = pos;
	_size = Vector2(50, 120);
	_direction = direction;
	_active = true;

	_isActiveInteraction = false;
	_isClose = false;
}

void GateNpc::release()
{
	_ani->release();
	delete _ani;
}

void GateNpc::update(float timeElapsed)
{
	Npc::update(timeElapsed);

	_ani->frameUpdate(timeElapsed);
}

void GateNpc::interaction()
{
	_uiMgr->showMap(true);
}

void GateNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	Npc::render();
}
