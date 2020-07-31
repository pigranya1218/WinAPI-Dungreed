#pragma once

class GameNode
{
private:
	bool _managerInit;

public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT init();			//초기화 전용 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 전용
	virtual void update();			//연산 전용
	virtual void render();			//그리기 전용

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

