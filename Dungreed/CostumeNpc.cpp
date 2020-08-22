#include "stdafx.h"
#include "CostumeNpc.h"
#include "UIManager.h"
#include "NpcManager.h"

void CostumeNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::COSTUME;
	_mapIcon = nullptr;
	_miniMapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_COSTUME");

	_img = IMAGE_MANAGER->findImage("NPC_ABILITY");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(10);
	_ani->start();

	_position = pos;
	_direction = direction;
	_size = Vector2(50, 76);
	_active = true;

	_name = L"��ν�";
	_bodyDialogue = L"�� �������� �غ�� �Ǽ̽��ϱ�?";
	_selectDialogues.push_back(L"�ǻ��");

	_isActiveInteraction = false;
	_isClose = false;
}

void CostumeNpc::release()
{
	_ani->release();
	delete _ani;
}

void CostumeNpc::update(float timeElapsed)
{
	Npc::update(timeElapsed);

	_ani->frameUpdate(timeElapsed);
}

void CostumeNpc::interaction()
{
	_uiMgr->setDialogue(this);
	_isActiveInteraction = true;
}

void CostumeNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	Npc::render();
}

void CostumeNpc::clickMenu(int menuIndex)
{
	if (menuIndex == 0)
	{
		_npcMgr->showCostumeUI();
	}
}
