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

	bool _isActive; // �ɼ�â�� �������� �Ǵ���
	map<KEY_TYPE, int> _keyMap; // Ű ���� ��
	map<SOUND_TYPE, float> _volumeMap; // ���� ���� ��

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

