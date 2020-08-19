#include "stdafx.h"
#include "RestaurantNpc.h"
#include "NpcManager.h"
#include "UIManager.h"

void RestaurantNpc::init(Vector2 pos, DIRECTION direction)
{
	_img = IMAGE_MANAGER->findImage("NPC_RESTAURANT");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(10);
	_ani->start();

	_position = pos;
	_direction = direction;

	_name = "ȣ����ī";
	_bodyDialogue = "�����ٶ󸶹ٻ������īŸ����";
	_selectDialogues.push_back("�Ĵ�");

	_isActive = false;
	_isClose = false;
}

void RestaurantNpc::release()
{
	_ani->release();
	delete _ani;
}

void RestaurantNpc::update(float timeElapsed)
{
	_ani->frameUpdate(timeElapsed);
	Vector2 playerPos = _npcMgr->getPlayerPos();
	if (!_isActive)
	{
		float distance = TTYONE_UTIL::getDistance(_position.x, _position.y, playerPos.x, playerPos.y);
		if (distance < 200)
		{
			_isClose = true;
		}
		else
		{
			_isClose = false;
		}
	}
	else
	{
	}

	if (_isClose) // �÷��̾�� ����� ��
	{
		if(!_isActive && KEY_MANAGER->isOnceKeyDown(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION)))
		{
			_uiMgr->setDialogue(this);
			_isActive = true;
		}
	}
}

void RestaurantNpc::render()
{
	_img->setScale(4);
	_img->aniRender(CAMERA->getRelativeV2(_position), _ani, (_direction == DIRECTION::LEFT));

	if (_isClose && !_isActive)
	{
		Vector2 renderPos = _position;
		renderPos.y -= 80;
		CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION))->setScale(4);
		CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION))->setAlpha(0.8);
		CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::INTERACTION))->render(CAMERA->getRelativeV2(renderPos));
	}
}
