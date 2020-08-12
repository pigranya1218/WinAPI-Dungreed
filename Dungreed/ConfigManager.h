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

	struct tagKeyButton
	{
		wstring actionName;
		FloatRect nameRc;
		FloatRect buttonRc;
	};

	struct tagCheckBox
	{
		wstring name;
		bool isCheck;
		float alpha;
		FloatRect textRc;
		FloatRect boxRc;
	};



	struct tagScrollBar
	{
		float totalHeight; // 총 높이
		float height; // 보여주는 높이
		float ratio; // 현재 스크롤의 비율
		FloatRect bgRc;
		FloatRect scrollRc;
	};

private:
	bool _isActive; // 옵션창을 열었는지 판단함

	Image* _header;
	Image* _background;
	Image* _soundBar;
	Image* _soundHandle;
	Image* _exitButton;
	FloatRect _exitRc;

	int _dragSoundIndex; // 드래그 중인지 판별, -1이면 드래그 아님
	int _keyButtonIndex; // 현재 마우스 위에 있는 키버튼, -1이면 없음
	float _keyChangeRemain; // 키 바꾸기 남은 시간
	bool _isScroll;
	map<ACTION_TYPE, int> _keyMap; // 키 설정 맵

	tagProgress _progressVolume[2];
	tagCheckBox _cameraShake;
	tagKeyButton _keyMapButton[static_cast<int>(ACTION_TYPE::END)];
	tagScrollBar _scrollBar;

	POINT _lastPtMouse;

private:
	wstring getActionName(ACTION_TYPE type);
	Image* getKeyImage(int key);

public:
	void init();
	void update();
	void render();

	inline void setActive(bool active) { _isActive = active; }
	inline bool isActive() const noexcept { return _isActive; }
	inline int getKey(ACTION_TYPE keyType) const noexcept { return _keyMap.find(keyType)->second; }
	inline float getVolume(SOUND_TYPE volumeType) const noexcept { return _progressVolume[static_cast<int>(volumeType)].ratio; }
	inline bool isCameraShake() const noexcept { return _cameraShake.isCheck; }
};

