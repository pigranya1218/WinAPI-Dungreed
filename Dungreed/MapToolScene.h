#pragma once
#include "GameNode.h"


class tileMapNode;

class MapToolScene : public GameNode
{
private:
	
	tileMapNode* _tileMapTool;

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����
};

