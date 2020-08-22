#include "stdafx.h"
#include "AbilityNpc.h"
#include "NpcManager.h"
#include "UIManager.h"

void AbilityNpc::init(Vector2 pos, DIRECTION direction)
{
	_type = NPC_TYPE::ABILITY;
	_mapIcon = nullptr;
	_miniMapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_ABILITY");

	_img = IMAGE_MANAGER->findImage("NPC_ABILITY");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(10);
	_ani->start();

	_position = pos;
	_direction = direction;
	_size = Vector2(50, 70);
	_active = true;

	_name = "ī��κ�";
	_bodyDialogue = "�ڳ� �Ա�! �Ʒ��� �ٰ�?";
	_selectDialogues.push_back("�Ʒ���");

	_isActiveInteraction = false;
	_isClose = false;
}

void AbilityNpc::release()
{
	_ani->release();
	delete _ani;
}

void AbilityNpc::update(float timeElapsed)
{
	Npc::update(timeElapsed);

	_ani->frameUpdate(timeElapsed);
}

void AbilityNpc::interaction()
{
	_uiMgr->setDialogue(this);
	_isActiveInteraction = true;
}

void AbilityNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	Npc::render();
}

void AbilityNpc::clickMenu(int menuIndex)
{
	if (menuIndex == 0)
	{
		_npcMgr->showAbilityUI();
	}
}
