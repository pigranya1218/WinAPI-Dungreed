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
	Image* _exitButton;
	FloatRect _exitRc;

	bool _isActive; // 옵션창을 열었는지 판단함
	map<KEY_TYPE, int> _keyMap; // 키 설정 맵
	map<SOUND_TYPE, float> _volumeMap; // 볼륨 설정 맵

	tagProgress _progressVolume[2];
	tagButton _controlButton;
	tagCheckBox 
		
public:
	void init();
	void update();
	void render();

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	inline int getKey(KEY_TYPE keyType) const noexcept { return _keyMap.find(keyType)->second; }
	inline float getVolume(SOUND_TYPE volumeType) const noexcept { return _volumeMap.find(volumeType)->second; }
};

