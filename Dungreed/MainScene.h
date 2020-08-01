#pragma once
#include "gameNode.h"

class MainScene : public GameNode
{
private:
	enum class MENU : UINT
	{
		PLAY = 0,
		OPTION,
		EXIT,
		END
	};

private:
	Image* _birdImage;
	Animation* _birdAni;
	Image* _frontCloud;
	Image* _backCloud;
	int _frontX;
	int _backX;
	int _frontSpeed;
	int _backSpeed;
	int _selectIndex;

	MENU _selected;
	FloatRect _selectedRc[static_cast<UINT>(MENU::END)];

private:
	string getImageName(string imageName, MENU menu) const;

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용
};

