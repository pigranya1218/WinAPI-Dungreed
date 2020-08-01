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
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
};

