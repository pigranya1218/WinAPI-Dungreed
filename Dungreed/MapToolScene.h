#pragma once
#include "GameNode.h"


class MapTool;

class MapToolScene : public GameNode
{
private:
	
	MapTool* _tileMapTool;

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용
};

