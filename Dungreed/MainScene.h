#pragma once
#include "gameNode.h"

class MainScene : public GameNode
{
private:
	Image* _birdImage;
	Animation* _ani;
	Image* _frontCloud;
	Image* _backCloud;
	int _frontX;
	int _backX;
	int _frontSpeed;
	int _backSpeed;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
};

