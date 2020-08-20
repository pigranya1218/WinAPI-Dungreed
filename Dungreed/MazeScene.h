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

	int _size;
	vector<vector<tagRoom>> _stage; // ��ü ��
	vector<vector<bool>> _isVisited; // �� ���� �湮�� ������ Ȯ��
	pair<int, int> _start;
	pair<int, int> _end;
	pair<int, int> _restaurant;
	pair<int, int> _shop;
	vector<pair<int, int>> _notUse;
	/*int _startX;
	int _startY;*/

public:
	virtual HRESULT init();			// �ʱ�ȭ ���� �Լ�
	virtual void release();			// �޸� ���� ����
	virtual void update();			// ���� ����
	virtual void render();			// �׸��� ����

	void makeRoom(int x, int y);
	bool makeSpecialRoom();
};

