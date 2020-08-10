#pragma once
#include "GameNode.h"

class GameScene : public GameNode
{
private:
	float _timeSpeed; // 시간 배속, 1 = 기본 속도


public:
	virtual HRESULT init();			// 초기화 전용 함수
	virtual void release();			// 메모리 해제 전용
	virtual void update();			// 연산 전용
	virtual void render();			// 그리기 전용

	// 플레이어 관련 함수



	// 스테이지 관련 함수



	// UI 관련 함수



};

