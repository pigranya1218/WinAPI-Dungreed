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

	vector<vector<tagRoom>> _stage; // 전체 맵
	vector<vector<bool>> _isVisited; // 각 방이 방문된 방인지 확인

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용

	void makeRoom(int x, int y);
};

