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
	vector<vector<tagRoom>> _stage; // 전체 맵
	vector<vector<bool>> _isVisited; // 각 방이 방문된 방인지 확인
	pair<int, int> _start;
	pair<int, int> _end;
	pair<int, int> _restaurant;
	pair<int, int> _shop;
	vector<pair<int, int>> _notUse;
	/*int _startX;
	int _startY;*/

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용

	void makeRoom(int x, int y);
	bool makeSpecialRoom();
};

