#include "stdafx.h"
#include "ChestNpc.h"
#include "ObjectManager.h"
#include "GoldObject.h"
#include "ItemObject.h"
#include "Item.h"

void ChestNpc::setInfo()
{
	switch (_rank)
	{
	case 0: // 베이직
	{
		_imgName = "NPC_CHEST_BASIC";
		_type = NPC_TYPE::CHEST_BASIC;
		_size = Vector2(40, 60);
	}
	break;
	case 1: // 블루
	{
		_imgName = "NPC_CHEST_BLUE";
		_type = NPC_TYPE::CHEST_BLUE;
		_size = Vector2(40, 60);
	}
	break;
	case 2: // 옐로
	{
		_imgName = "NPC_CHEST_YELLOW";
		_type = NPC_TYPE::CHEST_YELLOW;
		_size = Vector2(40, 90);
	}
	break;
	case 3: // 보스
	{
		_imgName = "NPC_CHEST_BOSS";
		_type = NPC_TYPE::CHEST_BOSS;
		_size = Vector2(40, 110);
	}
	break;
	}
	_img = IMAGE_MANAGER->findImage(_imgName);

}

Item* ChestNpc::getItem()
{
	switch (_rank)
	{
	case 0: // 베이직
	{
		return DATA_MANAGER->getRandomItem(ITEM_RANK::NORMAL, ITEM_RANK::HIGH, 1)[0];
	}
	break;
	case 1: // 블루
	{
		return DATA_MANAGER->getRandomItem(ITEM_RANK::HIGH, ITEM_RANK::RARE, 1)[0];
	}
	break;
	case 2: // 옐로
	{
		return DATA_MANAGER->getRandomItem(ITEM_RANK::RARE, ITEM_RANK::LEGEND, 1)[0];
	}
	break;
	case 3: // 보스
	{
		return DATA_MANAGER->getRandomItem(ITEM_RANK::LEGEND, ITEM_RANK::LEGEND, 1)[0];
	}
	break;
	}
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
	// 열리면서
	_isActiveInteraction = true;
	_img = IMAGE_MANAGER->findImage(_imgName + "_OPEN");

	// 돈과 아이템 배출
	Item* item = getItem();
	ItemObject* itemObject = new ItemObject;
	itemObject->setObjectManager(_objectMgr);
	itemObject->init(item, _position, 700, PI * 0.5);
	_objectMgr->pushObject(itemObject);

	for (int i = 0; i < 8; i++)
	{
		Vector2 pos = Vector2(RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x), RANDOM->getFromFloatTo(_position.y, _position.y - _size.y));
		float power = RANDOM->getFromFloatTo(600, 800);
		float radian = RANDOM->getFromFloatTo(0.2 * PI, 0.8 * PI);

		GoldObject* object = new GoldObject;
		object->setObjectManager(_objectMgr);
		object->init(10, pos, power, radian);
		_objectMgr->pushObject(object);
	}
	for (int i = 0; i < 4; i++)
	{
		Vector2 pos = Vector2(RANDOM->getFromFloatTo(_position.x - _size.x, _position.x + _size.x), RANDOM->getFromFloatTo(_position.y, _position.y - _size.y));
		float power = RANDOM->getFromFloatTo(600, 800);
		float radian = RANDOM->getFromFloatTo(0.2 * PI, 0.8 * PI);

		GoldObject* object = new GoldObject;
		object->setObjectManager(_objectMgr);
		object->init(100, pos, power, radian);
		_objectMgr->pushObject(object);
	}
}

void ChestNpc::render()
{
	_img->setScale(4);
	_img->render(CAMERA->getRelativeV2(_position));
	
	Npc::render();
}
