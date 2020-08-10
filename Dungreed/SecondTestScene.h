#pragma once
#include "GameNode.h"

class SampleStage;

class SecondTestScene :public GameNode
{
private:
	SampleStage* _stage;

public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용
};

