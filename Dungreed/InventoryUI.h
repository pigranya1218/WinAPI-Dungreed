#pragma once

class UIManager;

class InventoryUI
{
private:
	UIManager* _uiMgr;
	
	bool _isActive;

	Image* _baseImg;
	FloatRect _baseRc;

	FloatRect _exitRc;


public:
	void init(UIManager* uiMgr);
	void release();
	void update(float elapsedTime);
	void render();

	bool isActive() const noexcept { return _isActive; }
	void setActive(bool active) { _isActive = active; }
};

