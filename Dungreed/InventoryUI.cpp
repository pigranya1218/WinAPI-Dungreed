#include "stdafx.h"
#include "InventoryUI.h"
#include "UIManager.h"

void InventoryUI::init()
{
	_isActive = false;

	_baseImg = IMAGE_MANAGER->findImage("UI/INVENTORY/BASE");
	_baseRc = FloatRect(980, 0, 1600, 900);

	_exitRc = FloatRect(900, 10, 980, 100);
}

void InventoryUI::release()
{
}

void InventoryUI::update(float elapsedTime)
{

}

void InventoryUI::render()
{
	_baseImg->render(_baseRc.getCenter(), _baseRc.getSize());
	if (_exitRc.ptInRect(_ptMouse))
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/EXIT_SELECTED")->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/EXIT")->render(_exitRc.getCenter(), _exitRc.getSize());
	}
}
