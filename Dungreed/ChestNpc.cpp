#include "ChestNpc.h"

void ChestNpc::setInfo()
{
	switch (_rank)
	{
	case 0: // ������
	{
		_imgName = "NPC_CHEST_BASIC";
		_type = NPC_TYPE::CHEST_BASIC;
		_size = Vector2(40, 60);
	}
	break;
	case 1: // ���
	{
		_imgName = "NPC_CHEST_BLUE";
		_type = NPC_TYPE::CHEST_BLUE;
		_size = Vector2(40, 60);
	}
	break;
	case 2: // ����
	{
		_imgName = "NPC_CHEST_YELLOW";
		_type = NPC_TYPE::CHEST_YELLOW;
		_size = Vector2(40, 90);
	}
	break;
	case 3: // ����
	{
		_imgName = "NPC_CHEST_BOSS";
		_type = NPC_TYPE::CHEST_BOSS;
		_size = Vector2(40, 110);
	}
	break;
	}
	_img = IMAGE_MANAGER->findImage(_imgName);

}

void ChestNpc::init(Vector2 pos, DIRECTION direction)
{
	_mapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_CHEST");
	_miniMapIcon = IMAGE_MANAGER->findImage("UI/MAP/ICON_CHEST");

	_position = pos;
	_size = Vector2(50, 120);
	_direction = direction;
	_active = true;

	_isActiveInteraction = false;
	_isClose = false;

	setInfo();
}

void ChestNpc::interaction()
{
	// �����鼭
	_isActiveInteraction = true;
	_img = IMAGE_MANAGER->findImage(_imgName + "_OPEN");

	// ���� ������ ����
}

void ChestNpc::render()
{
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(_position));
	
	Npc::render();
}
