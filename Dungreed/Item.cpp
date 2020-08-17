#include "Item.h"

ITEM_TYPE Item::getItemType() const noexcept
{
	if ((_itemCode / 4096) == static_cast<int>(ITEM_TYPE::WEAPON_ONE_HAND) / 4096)
	{
		return ITEM_TYPE::WEAPON_ONE_HAND;
	}
	if ((_itemCode / 4096) == static_cast<int>(ITEM_TYPE::WEAPON_TWO_HAND) / 4096)
	{
		return ITEM_TYPE::WEAPON_TWO_HAND;
	}
	if ((_itemCode / 4096) == static_cast<int>(ITEM_TYPE::ACC) / 4096)
	{
		return ITEM_TYPE::ACC;
	}
	if ((_itemCode / 4096) == static_cast<int>(ITEM_TYPE::WEAPON_SUB) / 4096)
	{
		return ITEM_TYPE::WEAPON_SUB;
	}
	if ((_itemCode / 4096) == static_cast<int>(ITEM_TYPE::FOOD) / 4096)
	{
		return ITEM_TYPE::FOOD;
	}
}
