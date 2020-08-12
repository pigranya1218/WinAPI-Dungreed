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
		float totalHeight; // �� ����
		float height; // �����ִ� ����
		float ratio; // ���� ��ũ���� ����
		FloatRect bgRc;
		FloatRect scrollRc;
	};

private:
	bool _isActive; // �ɼ�â�� �������� �Ǵ���

	Image* _header;
	Image* _background;
	Image* _soundBar;
	Image* _soundHandle;
	Image* _exitButton;
	FloatRect _exitRc;

	int _dragSoundIndex; // �巡�� ������ �Ǻ�, -1�̸� �巡�� �ƴ�
	int _keyButtonIndex; // ���� ���콺 ���� �ִ� Ű��ư, -1�̸� ����
	float _keyChangeRemain; // Ű �ٲٱ� ���� �ð�
	bool _isScroll;
	map<ACTION_TYPE, int> _keyMap; // Ű ���� ��

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

