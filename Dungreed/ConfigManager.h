#pragma once
#include "SingletonBase.h"

class ConfigManager : public SingletonBase<ConfigManager>
{
private:
	Image* _header;
	Image* _background;
	Image* _exitButton;
	FloatRect _exitRc;

	bool _isActive; // �ɼ�â�� �������� �Ǵ���
	map<KEY_TYPE, int> _keyMap; // Ű ���� ��
	map<SOUND_TYPE, float> _volumeMap; // ���� ���� ��
		
public:
	void init();
	void update();
	void render();

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	inline int getKey(KEY_TYPE keyType) const noexcept { return _keyMap.find(keyType)->second; }
	inline float getVolume(SOUND_TYPE volumeType) const noexcept { return _volumeMap.find(volumeType)->second; }
};

