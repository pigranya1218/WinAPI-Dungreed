#include "stdafx.h"
#include "InventoryUI.h"
#include "Player.h"

void InventoryUI::init()
{
	_isActive = false;

	_baseImg = IMAGE_MANAGER->findImage("UI/INVENTORY/BASE");
	_baseRc = FloatRect(980, 0, 1600, 900);

	_exitRc = FloatRect(900, 10, 980, 100);

	_goldRc = FloatRect(1100, 798, 1500, 848);
}

void InventoryUI::release()
{
}

void InventoryUI::update(float elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_exitRc.ptInRect(_ptMouse))
		{
			_isActive = false;
		}
	}
}

void InventoryUI::render()
{
	// �⺻ �κ��丮 UI Ʋ
	_baseImg->render(_baseRc.getCenter(), _baseRc.getSize());
	
	// ��� ��ư
	if (_exitRc.ptInRect(_ptMouse))
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/EXIT_SELECTED")->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/EXIT")->render(_exitRc.getCenter(), _exitRc.getSize());
	}

	// ���� ���õ� ���� �׵θ�
	if (_player->getWeaponIndex() == 0)
	{
		Vector2 renderPos = Vector2(1165, 203);
		Vector2 renderSize = Vector2(238, 144);
		IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_0_SELECTED")->render(renderPos, renderSize);
	}
	else
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_1_SELECTED")->render(_exitRc.getCenter(), _exitRc.getSize());
	}

	D2D_RENDERER->renderTextField(_goldRc.left, _goldRc.top, to_wstring(_player->getGold()), RGB(255, 255, 255), _goldRc.getSize().y, _goldRc.getSize().x, _goldRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
}
