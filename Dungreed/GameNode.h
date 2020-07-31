#pragma once

class GameNode
{
private:
	bool _managerInit;

public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� ����
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

