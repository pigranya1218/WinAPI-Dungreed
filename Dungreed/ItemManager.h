#pragma once

class Item;
enum class ITEM_RANK;

class ItemManager
{
private:
	vector<Item*>	_items;

	map<int, Item*> _itemMap;

public:
	void init();
	void release();

	vector<Item*> getRandomItem(ITEM_RANK startRank, ITEM_RANK endRank, int count) const;
	inline Item* getItem(int itemCode) const;
};

