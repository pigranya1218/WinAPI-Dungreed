#pragma once
#include "GameNode.h"

class MazeScene : public GameNode
{
private:
	struct tagRoom 
	{
		FloatRect _rc;
		bool _isWall[4] = {false, false, false, false};
		bool _isVisited = false;
	};

	vector<vector<tagRoom>> _stage; // ��ü ��
	vector<vector<bool>> _isVisited; // �� ���� �湮�� ������ Ȯ��

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	void makeRoom(int x, int y);
};

