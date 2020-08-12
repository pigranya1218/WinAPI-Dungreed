#pragma once

class Player;

class InventoryUI
{
private:
	Player* _player;
	
	bool _isActive;

	Image* _baseImg;
	FloatRect _baseRc;

	FloatRect _exitRc;

	FloatRect _goldRc;


public:
	void setPlayer(Player* player) { _player = player; }

	void init();
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

