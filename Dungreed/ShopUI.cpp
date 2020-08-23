#include "stdafx.h"
#include "ShopUI.h"
#include "Player.h"
#include "Item.h"
#include <sstream>
#include <iomanip>

#include "BigPaintBlush.h"
#include "CosmosSword.h"
#include "GreenDadBat.h"
#include "MiniEarth.h"
#include "GatlingGun.h"

void ShopUI::drawWeaponInfo(Item* weapon, Vector2 pos, bool isRT, bool isSell)
{
	if (weapon == nullptr) return;

	FloatRect itemInfo;

	if (isRT)
	{
		itemInfo = FloatRect(pos, _itemInfo.getSize(), PIVOT::RIGHT_TOP);
	}
	else
	{
		itemInfo = FloatRect(pos, _itemInfo.getSize(), PIVOT::RIGHT_BOTTOM);
	}

	D2D_RENDERER->fillRectangle(itemInfo, 0, 0, 0, 0.75);

	PlayerStat itemStat = weapon->getAddStat();
	FloatRect nameRc = FloatRect(Vector2(itemInfo.left, itemInfo.top + 5), Vector2(itemInfo.getWidth(), 45.f), PIVOT::LEFT_TOP);

	{
		FloatRect mainRc = FloatRect(Vector2(itemInfo.left, nameRc.bottom + 10), Vector2(itemInfo.getWidth(), 80.f), PIVOT::LEFT_TOP);

		FloatRect imgRc = FloatRect(Vector2(mainRc.left + 20, mainRc.top), Vector2(80.f, mainRc.getHeight()), PIVOT::LEFT_TOP);
		IMAGE_MANAGER->findImage("UI/INVENTORY/INVEN_INFO")->render(imgRc.getCenter(), imgRc.getSize());
		weapon->getIconImg()->setScale(4);
		weapon->getIconImg()->render(imgRc.getCenter());

		D2D_RENDERER->renderTextField(nameRc.left, nameRc.top, weapon->getItemName(), getRankColor(weapon->getItemRank()), 48, nameRc.getWidth(), 45, 1, DWRITE_TEXT_ALIGNMENT_CENTER);

		FloatRect mainInfoRc = FloatRect(Vector2(imgRc.right + 20, mainRc.top), Vector2(200.f, mainRc.getHeight()), PIVOT::LEFT_TOP);
		Vector2 mainInfoTextPos1 = Vector2(mainInfoRc.left, mainInfoRc.getCenter().y - 25); // 공격력 적을 위치
		Vector2 mainInfoTextPos2 = Vector2(mainInfoRc.left, mainInfoRc.getCenter().y); // 공격속도 적을 위치
		D2D_RENDERER->renderTextField(mainInfoTextPos1.x, mainInfoTextPos1.y, L"공격력 : ", RGB(255, 255, 255), 26, 150, 25);
		D2D_RENDERER->renderTextField(mainInfoTextPos1.x + 80, mainInfoTextPos1.y, to_wstring(static_cast<int>(itemStat.minDamage)) + L" ~ " + to_wstring(static_cast<int>(itemStat.maxDamage)),
			RGB(255, 212, 0), 26, 150, 25, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
		D2D_RENDERER->renderTextField(mainInfoTextPos2.x, mainInfoTextPos2.y, L"공격 속도 : ", RGB(255, 255, 255), 26, 150, 25);

		stringstream stream;
		stream << fixed << setprecision(2) << itemStat.attackSpeed;
		D2D_RENDERER->renderTextField(mainInfoTextPos2.x + 100, mainInfoTextPos2.y, TTYONE_UTIL::stringTOwsting(stream.str()),
			RGB(255, 212, 0), 26, 150, 25, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");

		int count = 0;
		vector<wstring> displayBonusOption = weapon->getDisplayInfos();
		for (int i = 0; i < displayBonusOption.size(); i++)
		{
			Vector2 bonusPos = Vector2(mainRc.left + 20, mainInfoRc.bottom + 10 + 28 * count);
			count++;
			D2D_RENDERER->renderTextField(bonusPos.x, bonusPos.y, L"▶", RGB(255, 255, 255), 23, 25, 25);
			D2D_RENDERER->renderTextField(bonusPos.x + 30, bonusPos.y, displayBonusOption[i], RGB(0, 255, 0), 23, 400, 25);
		}
		for (int i = 0; i < static_cast<int>(STAT_TYPE::END); i++)
		{
			STAT_TYPE statType = static_cast<STAT_TYPE>(i);
			if (statType == STAT_TYPE::MIN_DAMAGE || statType == STAT_TYPE::MAX_DAMAGE || statType == STAT_TYPE::ATTACK_SPEED) continue;
			int statValue = itemStat.getStat(statType);
			if (statValue != 0)
			{
				Vector2 bonusPos = Vector2(mainRc.left + 20, mainInfoRc.bottom + 10 + 28 * count);
				count++;
				D2D_RENDERER->renderTextField(bonusPos.x, bonusPos.y, L"▶", RGB(255, 255, 255), 23, 25, 25, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
				D2D_RENDERER->renderTextField(bonusPos.x + 25, bonusPos.y, ((statValue > 0) ? L"+" : L"") + to_wstring(statValue), (statValue > 0) ? (RGB(0, 255, 0)) : (RGB(255, 0, 0)), 23, 400, 25, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
				int size = TTYONE_UTIL::getSize(statValue);
				D2D_RENDERER->renderTextField(bonusPos.x + 25 + size * 17 + 8, bonusPos.y, TTYONE_UTIL::stringTOwsting(itemStat.getStatString(statType, false)), RGB(255, 255, 255), 23, 400, 25);
			}
		}

		Vector2 rankPos = Vector2(mainRc.left + 20, mainInfoRc.bottom + 20 + 25 * count);
		drawItemRank(rankPos, weapon->getItemRank());

		Vector2 typePos = Vector2(mainRc.left + 20, rankPos.y + 30);
		drawItemType(typePos, weapon->getItemType());

		int lineSize = weapon->getDisplayText().size() * 21 / 400 + 1;
		Vector2 textPos = Vector2(mainRc.left + 20, typePos.y + 29);
		D2D_RENDERER->renderTextField(textPos.x, textPos.y, weapon->getDisplayText(), RGB(202, 255, 255), 21, 400, 21 * lineSize, 1, DWRITE_TEXT_ALIGNMENT_LEADING);

		Vector2 goldPos = Vector2(mainRc.right - 100, textPos.y + 29 * lineSize);
		int price = weapon->getPrice();
		if (isSell)
		{
			price = price / 10 * 7;
		}
		D2D_RENDERER->renderTextField(goldPos.x, goldPos.y, to_wstring(price), RGB(255, 255, 255), 21, 80, 21, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
		_goldImg->setScale(4);
		_goldImg->render(Vector2(goldPos.x, goldPos.y + 12));

	}
}

void ShopUI::drawAccInfo(Item* acc, Vector2 pos, bool isRT, bool isSell)
{
	if (acc == nullptr) return;

	FloatRect itemInfo;

	if (isRT)
	{
		itemInfo = FloatRect(pos, _itemInfo.getSize(), PIVOT::RIGHT_TOP);
	}
	else
	{
		itemInfo = FloatRect(pos, _itemInfo.getSize(), PIVOT::RIGHT_BOTTOM);
	}

	D2D_RENDERER->fillRectangle(itemInfo, 0, 0, 0, 0.75);

	PlayerStat itemStat = acc->getAddStat();
	FloatRect nameRc = FloatRect(Vector2(itemInfo.left, itemInfo.top + 5), Vector2(itemInfo.getWidth(), 45.f), PIVOT::LEFT_TOP);

	{
		FloatRect mainRc = FloatRect(Vector2(itemInfo.left, nameRc.bottom + 10), Vector2(itemInfo.getWidth(), 80.f), PIVOT::LEFT_TOP);

		FloatRect imgRc = FloatRect(Vector2(mainRc.left + 20, mainRc.top), Vector2(80.f, mainRc.getHeight()), PIVOT::LEFT_TOP);
		IMAGE_MANAGER->findImage("UI/INVENTORY/INVEN_INFO")->render(imgRc.getCenter(), imgRc.getSize());
		acc->getIconImg()->setScale(4);
		acc->getIconImg()->render(imgRc.getCenter());

		D2D_RENDERER->renderTextField(nameRc.left, nameRc.top, acc->getItemName(), getRankColor(acc->getItemRank()), 48, nameRc.getWidth(), 45, 1, DWRITE_TEXT_ALIGNMENT_CENTER);

		FloatRect mainInfoRc = FloatRect(Vector2(imgRc.right + 20, mainRc.top), Vector2(200.f, mainRc.getHeight()), PIVOT::LEFT_TOP);

		int count = 0;
		vector<wstring> displayBonusOption = acc->getDisplayInfos();
		for (int i = 0; i < displayBonusOption.size(); i++)
		{
			Vector2 bonusPos = Vector2(mainRc.left + 20, mainInfoRc.bottom + 10 + 28 * count);
			count++;
			D2D_RENDERER->renderTextField(bonusPos.x, bonusPos.y, L"▶", RGB(255, 255, 255), 23, 25, 25);
			D2D_RENDERER->renderTextField(bonusPos.x + 30, bonusPos.y, displayBonusOption[i], RGB(0, 255, 0), 23, 400, 25);
		}
		for (int i = 0; i < static_cast<int>(STAT_TYPE::END); i++)
		{
			STAT_TYPE statType = static_cast<STAT_TYPE>(i);
			int statValue = itemStat.getStat(statType);
			if (statValue != 0)
			{
				Vector2 bonusPos = Vector2(mainRc.left + 20, mainInfoRc.bottom + 10 + 28 * count);
				count++;
				D2D_RENDERER->renderTextField(bonusPos.x, bonusPos.y, L"▶", RGB(255, 255, 255), 23, 25, 25, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
				D2D_RENDERER->renderTextField(bonusPos.x + 25, bonusPos.y, ((statValue > 0) ? L"+" : L"") + to_wstring(statValue), (statValue > 0) ? (RGB(0, 255, 0)) : (RGB(255, 0, 0)), 23, 400, 25, 1, DWRITE_TEXT_ALIGNMENT_LEADING, L"Aa카시오페아");
				int size = TTYONE_UTIL::getSize(statValue);
				D2D_RENDERER->renderTextField(bonusPos.x + 25 + size * 17 + 8, bonusPos.y, TTYONE_UTIL::stringTOwsting(itemStat.getStatString(statType, false)), RGB(255, 255, 255), 23, 400, 25);
			}
		}

		Vector2 rankPos = Vector2(mainRc.left + 20, mainInfoRc.bottom + 20 + 25 * count);
		drawItemRank(rankPos, acc->getItemRank());

		Vector2 typePos = Vector2(mainRc.left + 20, rankPos.y + 30);
		drawItemType(typePos, acc->getItemType());

		int lineSize = acc->getDisplayText().size() * 21 / 400 + 1;
		Vector2 textPos = Vector2(mainRc.left + 20, typePos.y + 29);
		D2D_RENDERER->renderTextField(textPos.x, textPos.y, acc->getDisplayText(), RGB(202, 255, 255), 21, 400, 21 * lineSize, 1, DWRITE_TEXT_ALIGNMENT_LEADING);
	
		Vector2 goldPos = Vector2(mainRc.right - 100, textPos.y + 29 * lineSize);
		int price = acc->getPrice();
		if (isSell)
		{
			price = price / 10 * 7;
		}
		D2D_RENDERER->renderTextField(goldPos.x, goldPos.y, to_wstring(price), RGB(255, 255, 255), 21, 80, 21, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
		_goldImg->setScale(4);
		_goldImg->render(Vector2(goldPos.x, goldPos.y + 12));
	}
}

void ShopUI::drawInvenInfo(int index, Vector2 pos)
{
	Item* item = _player->getInvenItem(index);
	if (item == nullptr) return;
	if (item->getItemType() == ITEM_TYPE::ACC)
	{
		drawAccInfo(item, pos, false, true);
	}
	else
	{
		drawWeaponInfo(item, pos, false, true);
	}
}

void ShopUI::drawShopInfo(int index)
{
	Item* item = _shopItem[index];
	if (item == nullptr) return;
	if (item->getItemType() == ITEM_TYPE::ACC)
	{
		if (index <= 2)
		{
			drawAccInfo(item, Vector2(1010.f, _shopItemRc[index].getCenter().y), true, false);
		}
		else
		{
			drawAccInfo(item, Vector2(1010.f, _shopItemRc[index].getCenter().y), false, false);
		}
	}
	else
	{
		if (index <= 2)
		{
			drawWeaponInfo(item, Vector2(1010.f, _shopItemRc[index].getCenter().y), true, false);
		}
		else
		{
			drawWeaponInfo(item, Vector2(1010.f, _shopItemRc[index].getCenter().y), false, false);
		}
	}
}

void ShopUI::drawItemType(Vector2 pos, ITEM_TYPE type)
{
	switch (type)
	{
	case ITEM_TYPE::WEAPON_ONE_HAND:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"한손 (주무기)", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	case ITEM_TYPE::WEAPON_TWO_HAND:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"양손무기", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	case ITEM_TYPE::ACC:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"액세서리", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	}
}

void ShopUI::drawItemRank(Vector2 pos, ITEM_RANK rank)
{
	switch (rank)
	{
	case ITEM_RANK::NORMAL:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"일반 아이템", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	case ITEM_RANK::HIGH:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"고급 아이템", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	case ITEM_RANK::RARE:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"희귀 아이템", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	case ITEM_RANK::LEGEND:
	{
		D2D_RENDERER->renderTextField(pos.x, pos.y, L"전설 아이템", RGB(180, 180, 180), 22, 200, 25, 1);
	}
	break;
	}
}

COLORREF ShopUI::getRankColor(ITEM_RANK rank)
{
	switch (rank)
	{
	case ITEM_RANK::NORMAL:
	{
		return RGB(255, 255, 255);
	}
	break;
	case ITEM_RANK::HIGH:
	{
		return RGB(43, 123, 255);
	}
	break;
	case ITEM_RANK::RARE:
	{
		return RGB(255, 210, 0);
	}
	break;
	case ITEM_RANK::LEGEND:
	{
		return RGB(255, 0, 120);
	}
	break;
	}
}

void ShopUI::init()
{
	_isActive = false;

	_baseImg = IMAGE_MANAGER->findImage("UI/INVENTORY/BASE");
	_baseRc = FloatRect(980, 0, 1600, 900);

	_accImg = IMAGE_MANAGER->findImage("UI/INVENTORY/ACC_ZONE");
	_accRc = FloatRect(Vector2(1305, 352), Vector2(460, 110), PIVOT::CENTER);

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

	_itemInfo = FloatRect(Vector2(0, 0), Vector2(450, 370), PIVOT::CENTER);

	_goldImg = IMAGE_MANAGER->findImage("UI/SHOP/GOLD");
	_shopBaseImg = IMAGE_MANAGER->findImage("UI/SHOP/BASE");
	_shopBaseRc = FloatRect(0, 0, 600, 900);

	_shopItemBaseImg = IMAGE_MANAGER->findImage("UI/SHOP/ITEM_BASE");
	for (int i = 0; i < 5; i++)
	{
		_shopItemRc[i] = FloatRect(35, 150 + (120 * i), 550, 270 + (120 * i));
		
	}

	// FOR TEST
	Item* item1 = new BigPaintBlush;
	item1->init();
	_shopItem.push_back(item1);
	Item* item2 = new CosmosSword;
	item2->init();
	_shopItem.push_back(item2);
	Item* item3 = new GreenDadBat;
	item3->init();
	_shopItem.push_back(item3);
	Item* item4 = new miniEarth;
	item4->init();
	_shopItem.push_back(item4);
	Item* item5 = new GatlingGun;
	item5->init();
	_shopItem.push_back(item5);
}

void ShopUI::release()
{
}

void ShopUI::update(float elapsedTime)
{
	if (KEY_MANAGER->isOnceKeyDown(VK_LBUTTON))
	{
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
		// 무기칸 위에 있던 경우 장착 해제
		for (int i = 0; i < 2; i++)
		{
			if (_equippedWeaponRc[i * 2].ptInRect(_ptMouse))
			{
				_player->unequipWeapon(i);
				break;
			}
		}

		// 악세사리칸 위에 있던 경우 장착 해제
		for (int i = 0; i < 4; i++)
		{
			if (_equippedAccRc[i].ptInRect(_ptMouse))
			{
				_player->unequipAcc(i);
				break;
			}
		}

		// 인벤토리 위에 있던 경우 판매
		for (int i = 0; i < 15; i++)
		{
			if (_invenRc[i].ptInRect(_ptMouse))
			{
				_player->sellItem(i);
				break;
			}
		}

		// 상점 위에 있던 경우 구매
		for (int i = 0; i < _shopItem.size(); i++)
		{
			if (_shopItemRc[i].ptInRect(_ptMouse))
			{
				if (_player->buyItem(_shopItem[i]))
				{
					_shopItem.erase(_shopItem.begin() + i);
				}
			}
		}
	}
}

void ShopUI::render()
{
	// 기본 인벤토리 UI 틀
	_baseImg->render(_baseRc.getCenter(), _baseRc.getSize());

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

			if (weapon->getItemType() == ITEM_TYPE::WEAPON_TWO_HAND)
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


	for (int i = 0; i < 15; i++)
	{
		if (_invenRc[i].ptInRect(_ptMouse))
		{
			drawInvenInfo(i, _invenRc[i].getCenter());
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (_equippedWeaponRc[i * 2].ptInRect(_ptMouse))
		{
			drawWeaponInfo(_player->getWeapon(i), _equippedWeaponRc[i * 2].getCenter(), true, true);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (_equippedAccRc[i].ptInRect(_ptMouse))
		{
			drawAccInfo(_player->getAcc(i), _equippedAccRc[i].getCenter(), true, true);
		}
	}

	// SHOP
	_shopBaseImg->render(_shopBaseRc.getCenter(), _shopBaseRc.getSize());

	for (int i = 0; i < _shopItem.size(); i++)
	{
		// D2D_RENDERER->fillRectangle(_shopItemRc[i]);
		FloatRect iconRc = FloatRect(_shopItemRc[i].left, _shopItemRc[i].top, _shopItemRc[i].left + 90, _shopItemRc[i].bottom);
		_shopItem[i]->getIconImg()->setScale(4);
		_shopItem[i]->getIconImg()->render(iconRc.getCenter());
		FloatRect baseRc = FloatRect(_shopItemRc[i].left + 100, _shopItemRc[i].top, _shopItemRc[i].right, _shopItemRc[i].bottom);
		if (_shopItemRc[i].ptInRect(_ptMouse))
		{
			IMAGE_MANAGER->findImage("UI/SHOP/ITEM_BASE_SELECTED")->render(baseRc.getCenter());
			drawShopInfo(i);
		}
		else
		{
			_shopItemBaseImg->render(baseRc.getCenter());
		}
		
		D2D_RENDERER->renderTextField(baseRc.left + 15, baseRc.top + 15, _shopItem[i]->getItemName(), getRankColor(_shopItem[i]->getItemRank()), 43, baseRc.getWidth(), 45, 1, DWRITE_TEXT_ALIGNMENT_LEADING);
		D2D_RENDERER->renderTextField(baseRc.left + 15, baseRc.bottom - 54, to_wstring(_shopItem[i]->getPrice()), RGB(255, 255, 255), 38, 340, 38, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
	}
	IMAGE_MANAGER->findImage("KEY_ESC")->setScale(3);
	IMAGE_MANAGER->findImage("KEY_ESC")->render(Vector2(390, 800));
	D2D_RENDERER->renderTextField(200, 780, L"나가기", RGB(255, 255, 255), 43, 340, 38, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);

}
