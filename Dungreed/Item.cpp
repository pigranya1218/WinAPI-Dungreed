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
}

ITEM_RANK Item::getItemRank() const noexcept
{
	if (((_itemCode % 4096) / 256) == static_cast<int>(ITEM_RANK::NORMAL) / 256)
	{
		return ITEM_RANK::NORMAL;
	}
	if (((_itemCode % 4096) / 256) == static_cast<int>(ITEM_RANK::HIGH) / 256)
	{
		return ITEM_RANK::HIGH;
	}
	if (((_itemCode % 4096) / 256) == static_cast<int>(ITEM_RANK::RARE) / 256)
	{
		return ITEM_RANK::RARE;
	}
	if (((_itemCode % 4096) / 256) == static_cast<int>(ITEM_RANK::LEGEND) / 256)
	{
		return ITEM_RANK::LEGEND;
	}
}
