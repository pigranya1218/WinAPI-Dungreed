#pragma once

class Player;

class InventoryUI
{
private:
	Player* _player;
	
	bool _isActive;

	Image* _baseImg;
	FloatRect _baseRc;

	Image* _accImg;
	FloatRect _accRc;

	FloatRect _exitRc;

	FloatRect _goldRc;

	FloatRect _equippedWeaponRc[4];
	FloatRect _equippedAccRc[4];
	FloatRect _invenRc[15];

public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

