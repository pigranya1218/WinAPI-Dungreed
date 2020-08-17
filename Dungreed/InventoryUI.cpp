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

	_exitRc = FloatRect(890, 10, 980, 90);

	_goldRc = FloatRect(1100, 803, 1505, 848);

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

	_dragWeaponIndex = -1;
	_dragAccIndex = -1;
	_dragInvenIndex = -1;
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

		// 드래그
		// 무기칸 위에 있던 경우
		for (int i = 0; i < 2; i++)
		{
			if (_equippedWeaponRc[i * 2].ptInRect(_ptMouse))
			{
				_dragWeaponIndex = i;
				break;
			}
		}

		// 악세사리칸 위에 있던 경우
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAccRc[i].ptInRect(_ptMouse))
			{
				_dragAccIndex = i;
				break;
			}
		}


		// 인벤토리 위에 있던 경우
		for (int i = 0; i < 15; i++)
		{
			if (_invenRc[i].ptInRect(_ptMouse))
			{
				_dragInvenIndex = i;
				break;
			}
		}
	}

	// 드래그 해제
	if (KEY_MANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_dragWeaponIndex != -1) // 무기를 잡고 있던 경우
		{
			// 무기칸 위에 있던 경우
			for (int i = 0; i < 2; i++)
			{
				if (_equippedWeaponRc[i * 2].ptInRect(_ptMouse))
				{
					_player->swapItem(_dragWeaponIndex, i);
					break;
				}
			}

			// 인벤토리 위에 있던 경우
			for (int i = 0; i < 15; i++)
			{
				if (_invenRc[i].ptInRect(_ptMouse))
				{
					_player->swapItem(_dragWeaponIndex, 6 + i);
					break;
				}
			}

			// TODO : 파괴하기
		}
		else if (_dragAccIndex != -1)
		{
			// 악세칸 위에 있던 경우
			for (int i = 0; i < 4; i++)
			{
				if (_equippedAccRc[i].ptInRect(_ptMouse))
				{
					_player->swapItem(2 + _dragAccIndex, 2 + i);
					break;
				}
			}

			// 인벤토리 위에 있던 경우
			for (int i = 0; i < 15; i++)
			{
				if (_invenRc[i].ptInRect(_ptMouse))
				{
					_player->swapItem(2 + _dragAccIndex, 6 + i);
					break;
				}
			}

			// TODO : 파괴하기
		}
		else if (_dragInvenIndex != -1)
		{
			// 무기칸 위에 있던 경우
			for (int i = 0; i < 2; i++)
			{
				if (_equippedWeaponRc[i * 2].ptInRect(_ptMouse))
				{
					_player->swapItem(6 + _dragInvenIndex, i);
					break;
				}
			}

			// 악세사리 위에 있던 경우
			for (int i = 0; i < 4; i++)
			{
				if (_equippedAccRc[i].ptInRect(_ptMouse))
				{
					_player->swapItem(6 + _dragInvenIndex, 2 + i);
					break;
				}
			}

			// 인벤토리 위에 있던 경우
			for (int i = 0; i < 15; i++)
			{
				if (_invenRc[i].ptInRect(_ptMouse))
				{
					_player->swapItem(6 + _dragInvenIndex, 6 + i);
					break;
				}
			}

			// TODO : 파괴하기

		}

		_dragWeaponIndex = -1;
		_dragAccIndex = -1;
		_dragInvenIndex = -1;
	}



	if (KEY_MANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		// 무기칸 위에 있던 경우
		for (int i = 0; i < 2; i++)
		{
			if (_equippedWeaponRc[i * 2].ptInRect(_ptMouse))
			{
				_player->unequipWeapon(i);
				break;
			}
		}

		// 악세사리칸 위에 있던 경우
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAccRc[i].ptInRect(_ptMouse))
			{
				_player->unequipAcc(i);
				break;
			}
		}


		// 인벤토리 위에 있던 경우
		for (int i = 0 ; i < 15 ; i++)
		{
			if (_invenRc[i].ptInRect(_ptMouse))
			{
				_player->equipItem(i);
				break;
			}
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

			weapon->getIconImg()->setScale(5);
			weapon->getIconImg()->render(_equippedWeaponRc[i * 2].getCenter());

			if (weapon->getType() == ITEM_TYPE::WEAPON_TWO_HAND)
			{
				IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_X")->setScale(5);
				IMAGE_MANAGER->findImage("UI/INVENTORY/WEAPON_X")->render(_equippedWeaponRc[i * 2 + 1].getCenter());
			}
		}

		for (int i = 0; i < 4; i++)
		{
			Item* acc = _player->getAcc(i);
			if (acc == nullptr) continue;

			acc->getIconImg()->setScale(5);
			acc->getIconImg()->render(_equippedAccRc[i].getCenter());
		}
	}

	// 인벤토리 그리기
	{
		for (int i = 0; i < 15; i++)
		{
			Item* item = _player->getInvenItem(i);
			if (item == nullptr) continue;

			item->getIconImg()->setScale(5);
			item->getIconImg()->render(_invenRc[i].getCenter());
		}
	}

	// 골드 적기	
	D2D_RENDERER->renderTextField(_goldRc.left, _goldRc.top, to_wstring(_player->getGold()), RGB(255, 255, 255), _goldRc.getSize().y, _goldRc.getSize().x, _goldRc.getSize().y, 1, DWRITE_TEXT_ALIGNMENT_TRAILING, L"Alagard");


	// 드래그 중이라면 마우스 위치에 아이템 그리기
	if (_dragWeaponIndex != -1)
	{
		if (_player->getWeapon(_dragWeaponIndex) != nullptr)
		{
			_player->getWeapon(_dragWeaponIndex)->getIconImg()->setScale(5);
			_player->getWeapon(_dragWeaponIndex)->getIconImg()->render(Vector2(_ptMouse));
		}
	}
	else if (_dragAccIndex != -1)
	{
		if (_player->getAcc(_dragAccIndex) != nullptr)
		{
			_player->getAcc(_dragAccIndex)->getIconImg()->setScale(5);
			_player->getAcc(_dragAccIndex)->getIconImg()->render(Vector2(_ptMouse));
		}
	}
	else if (_dragInvenIndex != -1)
	{
		if (_player->getInvenItem(_dragInvenIndex) != nullptr)
		{
			_player->getInvenItem(_dragInvenIndex)->getIconImg()->setScale(5);
			_player->getInvenItem(_dragInvenIndex)->getIconImg()->render(Vector2(_ptMouse));
		}
	}
}
