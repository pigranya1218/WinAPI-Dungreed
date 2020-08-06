#pragma once
#include "SingletonBase.h"

class ConfigManager : public SingletonBase<ConfigManager>
{
private:
	struct tagProgress
	{
		wstring name;
		float ratio;
		FloatRect textRc;
		FloatRect progressRc;
		FloatRect handleRc;
	};

	struct tagButton
	{
		wstring name;
		FloatRect ButtonRc;
	};

	struct tagCheckBox
	{
		wstring name;
		bool isCheck;
		FloatRect textRc;
		FloatRect boxRc;
	};

private:
	Image* _header;
	Image* _background;
	Image* _soundBar;
	Image* _soundHandle;
	Image* _exitButton;
	FloatRect _exitRc;

	int _dragIndex; // 드래그 중인지 판별, -1이면 드래그 아님
	bool _isActive; // 옵션창을 열었는지 판단함
	map<KEY_TYPE, int> _keyMap; // 키 설정 맵

	tagProgress _progressVolume[2];
	tagCheckBox _cameraShake;
	tagButton _keyMapButton;
	
		
public:
	void init();
	void update();
	void render();

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	inline int getKey(KEY_TYPE keyType) const noexcept { return _keyMap.find(keyType)->second; }
	inline float getVolume(SOUND_TYPE volumeType) const noexcept { return _progressVolume[static_cast<int>(volumeType)].ratio; }
};

