#include "DoorNpc.h"
#include "StageManager.h"

void DoorNpc::setInfo()
{
	switch (_type)
	{
	case NPC_TYPE::ENTRANCE:
	{
		_type = NPC_TYPE::ENTRANCE;
		_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_ENTRANCE");
		_miniMapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_ENTRANCE");
		_size = Vector2(100, 260);

		_img = IMAGE_MANAGER->findImage("NPC_ENTRANCE");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(20);
		_ani->start();
		_isActiveInteraction = true;
	}
	break;
	case NPC_TYPE::EXIT:
	{
		_type = NPC_TYPE::EXIT;
		_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_EXIT");
		_miniMapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_EXIT");
		_size = Vector2(100, 260);
		
		_img = IMAGE_MANAGER->findImage("NPC_EXIT");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		_ani->setDefPlayFrame(false, false);
		_ani->setFPS(20);
		_isActiveInteraction = false;
	}
	break;
	}
}

void DoorNpc::init(Vector2 pos, DIRECTION direction)
{
	_position = pos;
	_direction = direction;
	
	_active = true;
	_isClose = false;

	setInfo();
}

void DoorNpc::release()
{
	if (_ani != nullptr)
	{
		_ani->release();
		delete _ani;
	}
}

void DoorNpc::update(float elapsedTime)
{
	if (_ani != nullptr)
	{
		_ani->frameUpdate(elapsedTime);
	}

	Npc::update(elapsedTime);
}

void DoorNpc::interaction() // 출구일 경우
{
	_npcMgr->nextStage();
	
}

void DoorNpc::render()
{
	if (_ani != nullptr)
	{
		_img->setScale(4);
		_img->aniRender(CAMERA->getRelativeV2(_position), _ani);
	}
	else
	{
		_img->setScale(4);
		_img->render(CAMERA->getRelativeV2(_position));
	}
	

	Npc::render();
}
