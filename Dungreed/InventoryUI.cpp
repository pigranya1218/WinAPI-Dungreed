#include "stdafx.h"
#include "InventoryUI.h"
#include "Player.h"
#include "Item.h"

void InventoryUI::init()
{
	_isActive = false;

	_baseImg = IMAGE_MANAGER->findImage("UI/INVENTORY/BASE");
	_baseRc = FloatRect(980, 0, 1600, 900);

	_accImg = IMAGE_MANAGER->findImage("UI/INVENTORY/ACC_ZONE");
	_accRc = FloatRect(Vector2(1305, 352), Vector2(460, 110), PIVOT::CENTER);

	_exitRc = FloatRect(900, 10, 980, 100);

	_goldRc = FloatRect(1100, 798, 1500, 848);

	_equippedWeaponRc[0] = rectMakePivot(Vector2(1108, 213), Vector2(96, 90), PIVOT::CENTER);
	_equippedWeaponRc[1] = rectMakePivot(Vector2(1220, 213), Vector2(96, 90), PIVOT::CENTER);
	_equippedWeaponRc[2] = rectMakePivot(Vector2(1380, 213), Vector2(96, 90), PIVOT::CENTER);
	_equippedWeaponRc[3] = rectMakePivot(Vector2(1492, 213), Vector2(96, 90), PIVOT::CENTER);

	_equippedAccRc[0] = rectMakePivot(Vector2(1140, 352), Vector2(96, 90), PIVOT::CENTER);
	_equippedAccRc[1] = rectMakePivot(Vector2(1250, 352), Vector2(96, 90), PIVOT::CENTER);
	_equippedAccRc[2] = rectMakePivot(Vector2(1360, 352), Vector2(96, 90), PIVOT::CENTER);
	_equippedAccRc[3] = rectMakePivot(Vector2(1470, 352), Vector2(96, 90), PIVOT::CENTER);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_invenRc[i * 5 + j] = rectMakePivot(Vector2(1080 + 110 * j, 490 + 105 * i), Vector2(96, 90), PIVOT::CENTER);
		}
	}
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
	// 기본 인벤토리 UI 틀
	_baseImg->render(_baseRc.getCenter(), _baseRc.getSize());
	
	// 취소 버튼
	if (_exitRc.ptInRect(_ptMouse))
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/EXIT_SELECTED")->render(_exitRc.getCenter(), _exitRc.getSize());
	}
	else
	{
		IMAGE_MANAGER->findImage("UI/INVENTORY/EXIT")->render(_exitRc.getCenter(), _exitRc.getSize());
	}

	// 현재 선택된 무기 테두리
	if (_player->getWeaponIndex() == 0)
	{
		Vector2 renderPos = Vector2(1164, 202);
		Vector2 renderSize = Vector2(236, 144);
		IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_0_SELECTED")->render(renderPos, renderSize);
	}
	else
	{
		Vector2 renderPos = Vector2(1436, 202);
		Vector2 renderSize = Vector2(236, 144);
		IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_1_SELECTED")->render(renderPos, renderSize);
	}

	// 무기 변경 키 그리기
	{
		Image* changeWeaponImg = CONFIG_MANAGER->getKeyImage(CONFIG_MANAGER->getKey(ACTION_TYPE::CHANGE_WEAPON));
		Vector2 renderPos = Vector2(1300, 176);
		changeWeaponImg->setScale(1);
		changeWeaponImg->render(renderPos);
	}

	// 인벤토리 칸 그리기
	{
		_accImg->render(_accRc.getCenter(), _accRc.getSize());
		for (int i = 0; i < 4; i++)
		{
			IMAGE_MANAGER->findImage("UI/INVENTORY/ACC_BASE")->render(_equippedAccRc[i].getCenter(), _equippedAccRc[i].getSize());
		}

		for (int i = 0; i < 15; i++)
		{
			if (_invenRc[i].ptInRect(_ptMouse))
			{
				IMAGE_MANAGER->findImage("UI/INVENTORY/INVEN_BASE_SELECTED")->render(_invenRc[i].getCenter(), _invenRc[i].getSize());
			}
			else
			{
				IMAGE_MANAGER->findImage("UI/INVENTORY/INVEN_BASE")->render(_invenRc[i].getCenter(), _invenRc[i].getSize());
			}
		}
	}

	// 마우스 위에 있는 칸에 대해 테두리 칠하기
	{
		for (int i = 0; i < 4; i++)
		{
			if (_equippedWeaponRc[i].ptInRect(_ptMouse))
			{
				IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_SELECTED")->render(_equippedWeaponRc[i].getCenter(), _equippedWeaponRc[i].getSize());
			}
		}

		for (int i = 0; i < 4; i++) 
		{
			if (_equippedAccRc[i].ptInRect(_ptMouse))
			{
				IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_SELECTED")->render(_equippedAccRc[i].getCenter(), _equippedAccRc[i].getSize());
			}
		}
	}
	
	// 장착한 장비 그리기
	{
		for (int i = 0; i < 2; i++)
		{
			Item* weapon = _player->getWeapon(i);
			if (weapon == nullptr) continue;

			weapon->getIconImg()->setScale(4);
			weapon->getIconImg()->render(_equippedWeaponRc[i * 2].getCenter());

			if (weapon->getType() == ITEM_TYPE::WEAPON_TWO_HAND)
			{
				IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_X")->setScale(5);
				IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_X")->render(_equippedWeaponRc[i * 2 + 1].getCenter());
			}
		}
	}


	

	D2D_RENDERER->renderTextField(_goldRc.left, _goldRc.top, to_wstring(_player->getGold()), RGB(255, 255, 255), _goldRc.getSize().y, _goldRc.getSize().x, _goldRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
}
