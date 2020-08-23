#pragma once


class Player;
class Item;
enum class ITEM_TYPE;
enum class ITEM_RANK;

class ShopUI
{
private:
	Player* _player;

	bool _isActive;

	// 인벤토리
	Image* _baseImg;
	FloatRect _baseRc;

	Image* _accImg;
	FloatRect _accRc;

	FloatRect _goldRc;

	FloatRect _equippedWeaponRc[4];
	FloatRect _equippedAccRc[4];
	FloatRect _invenRc[15];

	int _dragWeaponIndex;
	int _dragAccIndex;
	int _dragInvenIndex;

	FloatRect _itemInfo;

	// 상점
	Image* _goldImg;
	
	Image* _shopBaseImg;
	FloatRect _shopBaseRc;

	Image* _shopItemBaseImg;
	FloatRect _shopItemRc[5]; // 상점 아이템 칸
	vector<Item*> _shopItem; // 상점 아이템

private:
	void drawWeaponInfo(Item* weapon, Vector2 pos, bool isRT, bool isSell);
	void drawAccInfo(Item* acc, Vector2 pos, bool isRT, bool isSell);
	void drawInvenInfo(int index, Vector2 pos);
	void drawShopInfo(int index);

	void drawItemType(Vector2 pos, ITEM_TYPE type);
	void drawItemRank(Vector2 pos, ITEM_RANK rank);
	COLORREF getRankColor(ITEM_RANK rank);

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

