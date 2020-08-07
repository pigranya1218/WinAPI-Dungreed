#pragma once
#include "GameNode.h"


class MapTool;

class MapToolScene : public GameNode
{
private:
	
	MapTool* _tileMapTool;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
};

